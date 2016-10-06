// =========================================================================
//                    Copyright 2007-2015 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________


#include "breath/environment/windows_only/os_id.hpp"
#include "breath/environment/windows_only/windows_version_info.hpp"

#include <cstring>
#include <ostream>

namespace breath {


namespace {

// Attention: keep in sync with the declaration in [note 1]
static char const * const   
                    names[] =
{
    "Unknown Windows variant",
    "Win32s on Windows 3.1",

    "Windows 95",
    "Windows 98",
    "Windows Me",

    "Windows NT",
    "Windows 2000",
    "Windows XP",
    "Windows Server 2003",
    "Windows Home Server",
    "Windows Storage Server 2003",
    "Windows Server 2003 R2",
    "Windows XP Professional x64 Edition",
    "Windows Vista",
    "Windows Server 2008",
    "Windows Server 2008 R2",
    "Windows 7"

    // gps remove this, no? "Unidentified Windows version (not yet supported)"
    
} ;

}
// [note 1] Attention: keep in sync with the array declaration above
//
//     * windows_xp_professional_x64_edition is the only case where the
//       word "edition" appears directly as part os the OS name, rather
//       than in the edition name (as in "Web Edition", "Home Edition",
//       etc.) -- what should we do? leave "edition" or not?
//
// ordering:
//    initially, and at least for the Windows implementation, it was my
//    intent to support inequality comparisons:
//
//        // windows 2000 or later?
//        if( info.id() >= os_id::windows_2000 )
//
//    And the constants, in fact, appear in oldest-to-newest order.
//    But... 
//    I don't like too much the idea of having something which only
//    makes sense for one of the supported OSes, and perhaps not even
//    for it, in the future: right now, Windows
//    versions seem to have an established total ordering, but what
//    about the future? MS seems on the way of "parallelizing" their OS
//    products over a "client line" (Windows XP etc.) and a "server
//    line" (Windows Server 2003 etc.); in the future it seems to me
//    they could well release two Windows variants of which neither is <
//    or > than the other.
//
const os_id
        os_id::windows_unknown                    ( 0 ),
        os_id::win32s                             ( 1 ), // gps??
        os_id::windows_95                         ( 2 ),
        os_id::windows_98                         ( 3 ),
        os_id::windows_me                         ( 4 ),
        os_id::windows_nt                         ( 5 ), // unknown/3.51?? gps
        os_id::windows_2000                       ( 6 ),
        os_id::windows_xp                         ( 7 ),
        os_id::windows_server_2003                ( 8 ),
        os_id::windows_home_server                ( 9 ),
        os_id::windows_storage_server_2003        ( 10 ),
        os_id::windows_server_2003_r2             ( 11 ),
        os_id::windows_xp_professional_x64_edition( 12 ),  // gps leave "edition"?
        os_id::windows_vista                      ( 13 ),
        os_id::windows_server_2008                ( 14 ),
        os_id::windows_server_2008_r2             ( 15 ),
        os_id::windows_7                          ( 16 )
    ;


os_id::os_id( os_id::id_type n )
    : m_id( n )
{
}


bool
os_id::is_equal( const os_id & other ) const
{
    return m_id == other.m_id;
}

std::ostream &
operator<<( std::ostream & dest, const os_id & id )
{
    windows_version_info const
                        info ;
    
    dest << breath::names[ id.m_id ] ;
    char const * const  sps = info.service_pack_string() ;

    // Use C strings and strcmp here to workaround MSVC10
    // which chokes on == comparisons of std::string's;
    // don't use operator?:, for the same reason.
    //
    // We make no attempt to distinguish OSR2 vs. OSR2.1 vs.
    // OSR2.5 (how to do that, if possible at all, is
    // undocumented in the SDK).
    // ---------------------------------------------------------
    if ( id == os_id::windows_95 || id == os_id::windows_me
        && ( std::strcmp(sps, " C" ) == 0 || std::strcmp(sps, " B" ) ) ) {
        dest << " OSR2" ;
    } else if (id == os_id::windows_98 && std::strcmp( sps, " A" ) == 0 ) {
        dest << " Second Edition";
    } else {
        char const * const  edition = info.edition() ;
        if ( edition[0] != '\0' ) {
            dest << " " << edition ;
        }
        if ( sps[ 0 ] != '\0' ) {
            dest << " " << sps ;
        }
        if ( info.is_64_bit() ) {
            dest << ", 64-bit" ;
        }
    }
    
    return dest << " (" << info.major_version() << '.' << info.minor_version()
                << ", build " << info.build_number() << ")" ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
