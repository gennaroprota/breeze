// =========================================================================
//                    Copyright 2007-2017 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/environment/windows_only/windows_version_info.hpp"
#include "breath/diagnostics/last_api_error.hpp"
#include "breath/idiom/declare_non_copyable.hpp"
#include "breath/text/from_string.hpp"
#include "breath/text/to_string.hpp"

#undef UNICODE
#include <Windows.h>
#include <Lm.h>
#include <VersionHelpers.h>
#include <Wow64apiset.h>

#include <string>
#include <climits>

namespace breath {

namespace        {

//      RAII class to automatically close a registry key handle.
//
class key_handle_manager
{
public:
    BREATH_DECLARE_NON_COPYABLE( key_handle_manager )

    explicit key_handle_manager( HKEY key ) noexcept
        :   m_key( key )
    {
    }

    ~key_handle_manager() noexcept
    {
        // NOTE: the return value is ignored.
        RegCloseKey( m_key ) ;
    }

private:
    HKEY            m_key ;
} ;

[[ noreturn ]] void
raise_exception( char const * msg )
{
    throw breath::exception( msg ) ;
}

}

class windows_version_info::impl
{
public:
    BREATH_DECLARE_NON_COPYABLE( impl )

                    impl();
                    ~impl() noexcept;

    WKSTA_INFO_100 *
                    m_info = nullptr ;
} ;

windows_version_info::impl::impl()
{
    constexpr int       level = 100 ;
    NET_API_STATUS const
                        status = NetWkstaGetInfo( nullptr, level,
                                     reinterpret_cast< BYTE ** >( &m_info ) ) ;
    if ( status != NERR_Success ) {
        raise_exception( "cannot retrieve Windows version info" ) ;
    }
}

windows_version_info::impl::~impl() noexcept
{
    // Ignoring the return value (success or failure).
    NetApiBufferFree( m_info ) ;
}

windows_version_info::windows_version_info()
    :   m_impl( new windows_version_info::impl )
{
}

windows_version_info::~windows_version_info() noexcept
{
    delete m_impl ;
}

int
windows_version_info::major_version() const
{
    return m_impl->m_info->wki100_ver_major ;
}

int
windows_version_info::minor_version() const
{
    return m_impl->m_info->wki100_ver_minor ;
}

int
windows_version_info::build_number() const
{
    //      Take the Windows build number from the registry.
    //      In my registry there are both CurrentBuild and
    //      CurrentBuildNumber. Using the latter as it has a more
    //      explicit name. [gps]
    // -------------------------------------------------------------------
    HKEY                key = NULL;
    LONG const          ret = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
                              "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
                              0,
                              KEY_QUERY_VALUE | KEY_WOW64_32KEY,
                              &key ) ;
    if ( ret != ERROR_SUCCESS ) {
        raise_exception( "cannot open the CurrentVersion registry key" ) ;
    }
    key_handle_manager const
                        manager( key ) ;
    constexpr int       size = 256;
    DWORD               dw_size = size ;
    char                buffer[ size ] = {} ;
    int const           ret2 = RegGetValue( key, "", "CurrentBuildNumber",
                                 RRF_RT_ANY, nullptr,
                                 &buffer, &dw_size ) ;
    if ( ret2 != ERROR_SUCCESS ) {
        raise_exception( "cannot query the CurrentBuildNumber value"
                                                " from the registry" ) ;
    }
    return breath::from_string< int >( std::string( buffer ) ) ;
}

std::string
windows_version_info::edition() const
{
    // GetProductInfo() works only when major_version() >= 6.
    if( major_version() < 6 ) {
        return "" ;
    }

    DWORD               dw ;
    int const           failure = 0 ;
    if ( GetProductInfo( major_version(), minor_version(), 0, 0, &dw )
                                                                == failure ) {
        return "" ;
    }

    switch ( dw ) {
        case PRODUCT_BUSINESS:
            return "Business Edition" ;
        case PRODUCT_BUSINESS_N:
            return "Business N" ;
        case PRODUCT_CLUSTER_SERVER:
            return "HPC Edition" ;
        case PRODUCT_CLUSTER_SERVER_V:
            return "Server Hyper Core V" ;
        case PRODUCT_CORE:
            return "Home" ;
        case PRODUCT_CORE_COUNTRYSPECIFIC:
            return "Home China" ;
        case PRODUCT_CORE_N:
            return "Home N" ;
        case PRODUCT_CORE_SINGLELANGUAGE:
            return "Home Single Language" ;
        case PRODUCT_DATACENTER_EVALUATION_SERVER:
            return "Server Datacenter (evaluation installation)" ;
        case PRODUCT_DATACENTER_SERVER:
            return "Datacenter Edition" ;
        case PRODUCT_DATACENTER_SERVER_CORE:
            return "Server Datacenter (core installation)" ;
        case PRODUCT_DATACENTER_SERVER_CORE_V:
            return "Server Datacenter without Hyper-V (core installation)" ;
        case PRODUCT_DATACENTER_SERVER_V:
            return "Server Datacenter without Hyper-V (full installation)" ;
        //case PRODUCT_EDUCATION:
        //    return "Education" ;
        //case PRODUCT_EDUCATION_N:
        //    return "Education N" ;
        case PRODUCT_EMBEDDED:
            return "undocumented [PRODUCT_EMBEDDED]" ; //gps
        case PRODUCT_ENTERPRISE:
            return "Enterprise" ;
        case PRODUCT_ENTERPRISE_E:
            return "Enterprise E" ;
        case PRODUCT_ENTERPRISE_EVALUATION:
            return "PRODUCT_ENTERPRISE_EVALUATION" ;
        case PRODUCT_ENTERPRISE_N:
            return "Enterprise N" ;
        case PRODUCT_ENTERPRISE_N_EVALUATION:
            return "Enterprise N Evaluation" ;
        //case PRODUCT_ENTERPRISE_S:
        //    return "Enterprise 2015 LTSB" ;
        //case PRODUCT_ENTERPRISE_S_EVALUATION:
        //    return "Enterprise 2015 LTSB Evaluation" ;
        //case PRODUCT_ENTERPRISE_S_N:
        //    return "Enterprise 2015 LTSB N" ;
        //case PRODUCT_ENTERPRISE_S_N_EVALUATION:
        //    return "Enterprise 2015 LTSB N Evaluation" ;
        case PRODUCT_ENTERPRISE_SERVER:
            return "Server Enterprise (full installation)" ;
        case PRODUCT_ENTERPRISE_SERVER_CORE:
            return "Server Enterprise (core installation)" ;
        case PRODUCT_ENTERPRISE_SERVER_CORE_V:
            return "Server Enterprise without Hyper-V (core installation)" ;
        case PRODUCT_ENTERPRISE_SERVER_IA64:
            return "Server Enterprise for Itanium-based Systems" ;
        case PRODUCT_ENTERPRISE_SERVER_V:
            return "Server Enterprise without Hyper-V (full installation)" ;
        case PRODUCT_ESSENTIALBUSINESS_SERVER_ADDL:
            return "Essential Server Solution Additional" ;
        case PRODUCT_ESSENTIALBUSINESS_SERVER_ADDLSVC:
            return "Essential Server Solution Additional SVC" ;
        case PRODUCT_ESSENTIALBUSINESS_SERVER_MGMT:
            return "Essential Server Solution Management" ;
        case PRODUCT_ESSENTIALBUSINESS_SERVER_MGMTSVC:
            return "Essential Server Solution Management SVC" ;
        case PRODUCT_HOME_BASIC:
            return "Home Basic" ;
        case PRODUCT_HOME_BASIC_E:
            return "Home Basic E" ;
        case PRODUCT_HOME_BASIC_N:
            return "Home Basic N" ;
        case PRODUCT_HOME_PREMIUM:
            return "Home Premium" ;
        case PRODUCT_HOME_PREMIUM_E:
            return "Home Premium E" ;
        case PRODUCT_HOME_PREMIUM_N:
            return "Home Premium N" ;
        case PRODUCT_HOME_PREMIUM_SERVER:
            return "Home Server 2011" ;
        case PRODUCT_HOME_SERVER:
            return "Storage Server 2008 R2 Essentials" ;
        case PRODUCT_HYPERV:
            return "Microsoft Hyper-V Server" ;
        //case PRODUCT_IOTUAP:
        //    return "IoT Core" ;
        //case PRODUCT_IOTUAPCOMMERCIAL:
        //    return "IoT Core Commercial" ;
        case PRODUCT_MEDIUMBUSINESS_SERVER_MANAGEMENT:
            return "Essential Business Server Management Server" ;
        case PRODUCT_MEDIUMBUSINESS_SERVER_MESSAGING:
            return "Essential Business Server Messaging Server" ;
        case PRODUCT_MEDIUMBUSINESS_SERVER_SECURITY:
            return "Essential Business Server Security Server" ;
        case PRODUCT_MOBILE_CORE:
            return "Mobile" ;
        //case PRODUCT_MOBILE_ENTERPRISE:
        //    return "Mobile Enterprise" ;
        case PRODUCT_MULTIPOINT_PREMIUM_SERVER:
            return "MultiPoint Server Premium (full installation)" ;
        case PRODUCT_MULTIPOINT_STANDARD_SERVER:
            return "MultiPoint Server Standard (full installation)" ;
        case PRODUCT_PROFESSIONAL:
            return "Professional" ;
        case PRODUCT_PROFESSIONAL_E:
            return "Professional E" ;
        case PRODUCT_PROFESSIONAL_EMBEDDED:
            return "undocumented [PRODUCT_PROFESSIONAL_EMBEDDED]" ; // gps
        case PRODUCT_PROFESSIONAL_N:
            return "Professional N" ;
        case PRODUCT_PROFESSIONAL_WMC:
            return "Professional with Media Center" ;
        case PRODUCT_SB_SOLUTION_SERVER:
            return "Small Business Server 2011 Essentials" ;
        case PRODUCT_SB_SOLUTION_SERVER_EM:
            return "Server For SB Solutions EM" ;
        case PRODUCT_SERVER_FOR_SB_SOLUTIONS:
            return "Server For SB Solutions" ;
        case PRODUCT_SERVER_FOR_SB_SOLUTIONS_EM:
            return "Server For SB Solutions EM" ;
        case PRODUCT_SERVER_FOR_SMALLBUSINESS:
            return "for Windows Essential Server Solutions" ;
        case PRODUCT_SERVER_FOR_SMALLBUSINESS_V:
            return "without Hyper-V for Windows Essential Server Solutions" ;
        case PRODUCT_SERVER_FOUNDATION:
            return "Server Foundation" ;
        case PRODUCT_SMALLBUSINESS_SERVER:
            return "Small Business Server" ;
        case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:
            return "Small Business Server Premium" ;
        case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM_CORE:
            return "Small Business Server Premium (core installation)" ;
        case PRODUCT_SOLUTION_EMBEDDEDSERVER:
            return "MultiPoint Server" ;
        case PRODUCT_SOLUTION_EMBEDDEDSERVER_CORE:
            return "undocumented [PRODUCT_SOLUTION_EMBEDDEDSERVER_CORE]" ;// gps
        case PRODUCT_STANDARD_SERVER:
            return "Standard Edition" ;
        case PRODUCT_STANDARD_SERVER_CORE:
            return "Server Standard (core installation)" ;
        case PRODUCT_STANDARD_SERVER_CORE_V:
            return "Server Standard without Hyper-V (core installation)" ;
        case PRODUCT_STANDARD_SERVER_V:
            return "Server Standard without Hyper-V (full installation)" ;
        case PRODUCT_STANDARD_SERVER_SOLUTIONS:
            return "Server Solutions Premium " ;
        case PRODUCT_STANDARD_SERVER_SOLUTIONS_CORE:
            return "Server Solutions Premium (core installation)" ;
        case PRODUCT_STARTER:
            return "Starter" ;
        case PRODUCT_STARTER_E:
            return "Starter E" ;
        case PRODUCT_STARTER_N:
            return "Starter N" ;
        case PRODUCT_STORAGE_ENTERPRISE_SERVER:
            return "Storage Server Enterprise" ;
        case PRODUCT_STORAGE_ENTERPRISE_SERVER_CORE:
            return "Storage Server Enterprise (core installation)" ;
        case PRODUCT_STORAGE_EXPRESS_SERVER:
            return "Storage Server Express" ;
        case PRODUCT_STORAGE_EXPRESS_SERVER_CORE:
            return "Storage Server Express (core installation)" ;
        case PRODUCT_STORAGE_STANDARD_EVALUATION_SERVER:
            return "Storage Server Standard (evaluation installation)" ;
        case PRODUCT_STORAGE_STANDARD_SERVER:
            return "Storage Server Standard" ;
        case PRODUCT_STORAGE_STANDARD_SERVER_CORE:
            return "Storage Server Standard (core installation)" ;
        case PRODUCT_STORAGE_WORKGROUP_EVALUATION_SERVER:
            return "Storage Server Workgroup (evaluation installation)" ;
        case PRODUCT_STORAGE_WORKGROUP_SERVER:
            return "Storage Server Workgroup" ;
        case PRODUCT_STORAGE_WORKGROUP_SERVER_CORE:
            return "Storage Server Workgroup (core installation)" ;
        case PRODUCT_ULTIMATE:
            return "Ultimate" ;
        case PRODUCT_ULTIMATE_E:
            return "Ultimate E" ;
        case PRODUCT_ULTIMATE_N:
            return "Ultimate N" ;
        case PRODUCT_UNDEFINED:
            return "<undefined>" ;
        case PRODUCT_UNLICENSED:
            return "*unlicensed*" ;
        case PRODUCT_WEB_SERVER:
            return "Web Server (full installation)" ;
        case PRODUCT_WEB_SERVER_CORE:
            return "Web Server (core installation)" ;

        default:
            return "<unknown edition: " + breath::to_string( dw ) + ">" ;
    }
}

bool
windows_version_info::is_wow64_process()
{
    HMODULE const       module = GetModuleHandle( "kernel32" ) ;
    if ( module == NULL ) {
        throw breath::exception( "Cannot get a handle to kernel32.dll" ) ;
    }

    typedef BOOL ( WINAPI * fn_ptr_type )( HANDLE, PBOOL ) ;

    BOOL                is_wow64 = 0;
    fn_ptr_type const   is_wow64_process = reinterpret_cast< fn_ptr_type >(
                            GetProcAddress( module, "IsWow64Process" ) ) ;
    if ( is_wow64_process != nullptr ) {
        if ( is_wow64_process( GetCurrentProcess(), &is_wow64 ) == 0 )
        {
            throw last_api_error( "IsWow64Process failed" ) ;
        }
    }
    return is_wow64 != 0 ;
}

bool
windows_version_info::is_64_bit()
{
    // If the process is 64-bit and it runs at all, then it runs
    // on a 64-bit Windows version. Otherwise, it is a 32-bit process,
    // and the system is 64-bit if and only if the process runs under
    // WOW64.
    //
    return ( sizeof ( void * ) * CHAR_BIT == 64 )
        || is_wow64_process() ;
}

bool
windows_version_info::is_client()
{
    // It has no real impact on us, however this function is
    // documented to return a BOOL but declared to return a bool in
    // the corresponding header [last checked: November 2016].
    return IsWindowsServer() == 0 ;
}

std::string
windows_version_info::service_pack_string()
{
    HKEY                key = NULL;
    LONG const          ret = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
                              "SYSTEM\\CurrentControlSet\\Control\\Windows",
                              0,
                              KEY_QUERY_VALUE | KEY_WOW64_32KEY,
                              &key ) ;
    if ( ret != ERROR_SUCCESS ) {
        raise_exception( "cannot open the Control\\Windows registry key" ) ;
    }
    key_handle_manager const
                        manager( key ) ;
    DWORD               value ;
    DWORD               dw_size = sizeof value ;
    int                 ret2 = RegGetValue( key, "", "CSDVersion",
                                 RRF_RT_ANY, nullptr,
                                 &value, &dw_size ) ;
    if ( ret2 != ERROR_SUCCESS ) {
        raise_exception( "cannot query the CSDVersion value from"
                                                            " the registry" ) ;
    }

    int const           sp = value / 256 ;
    return sp == 0
        ? ""
        : "Service Pack " + breath::to_string( sp )
        ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
