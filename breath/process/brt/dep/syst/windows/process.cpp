// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/diagnostics/assert.hpp"
#include "breath/diagnostics/last_api_error.hpp"
#include "breath/process/exit_code.hpp"
#include "breath/process/private/handle.hpp"

#include <Windows.h>
#include <vector>

namespace breath {

class process::impl
{
public:
                        impl() : m_info()
                        {}
                        ~impl() noexcept
                        {
                            CloseHandle( m_info.hThread ) ;
                            CloseHandle( m_info.hProcess ) ;
                        }

    PROCESS_INFORMATION m_info ;
} ;

process::process()
    :   m_impl( new impl )
{
}

process::~process() noexcept
{
    delete m_impl ;
}

process::id_type
process::id() const
{
    return m_impl->m_info.dwProcessId ;
}

void
process::start( std::string const & app_name,
                std::string const & arguments,
                maybe< unsigned long > const & timeout_in_ms )
{
    std::vector< char > args( arguments.cbegin(), arguments.cend() ) ;
    args.resize( args.size() + 1 ) ;

    STARTUPINFOA        si = { sizeof si } ;
    DWORD const         creation_flags = ( GetConsoleWindow()
                                              ? 0
                                              : CREATE_NO_WINDOW ) ;

    int const           ret = CreateProcessA(
                                app_name.c_str(),
                                &args[ 0 ],
                                nullptr,
                                nullptr,
                                FALSE,
                                creation_flags,
                                nullptr,
                                nullptr,
                                &si,
                                &m_impl->m_info
                                ) ;
    if ( ret == 0 ) {
        throw last_api_error( "CreateProcess() failed" ) ;
    }

    if ( timeout_in_ms.is_valid() ) {
        BREATH_ASSERT( timeout_in_ms.value() > 0 ) ;
        if ( WaitForSingleObject( m_impl->m_info.hProcess,
                                 timeout_in_ms.value() ) == WAIT_FAILED ) {
            throw last_api_error( "WaitForSingleObject() failed" ) ;
        }
        try {
            terminate() ;
        } catch ( ... ) {
        }
    }
    //CloseHandle( pi.hThread ) ;
    //CloseHandle( pi.hProcess ) ;
}

void
process::kill()
{
    HANDLE const        h = OpenProcess( PROCESS_TERMINATE, false, m_impl->m_info.dwProcessId ) ;
    if ( h == NULL ) {
        throw last_api_error( "OpenProcess() failed" ) ;
    }
    if ( TerminateProcess( h, exit_failure ) == 0 ) {
        CloseHandle( h ) ;
        throw last_api_error( "TerminateProcess() failed" ) ;
    }
    if ( CloseHandle( h ) == 0 ) {
        throw last_api_error( "CloseHandle() failed" ) ;
    }
}

void
process::terminate()
{
    DWORD               exit_code ;
    if ( GetExitCodeProcess( m_impl->m_info.hProcess, &exit_code) == 0 ) {
        throw last_api_error( "GetExitCodeProcess() failed" ) ;
    }
    if ( exit_code == STILL_ACTIVE ) {
        HMODULE const       kernel = GetModuleHandleA( "kernel32.dll" ) ;
        if ( kernel == NULL ) {
            throw last_api_error( "GetModuleHandle() failed" ) ;
        }

        FARPROC             exit_proc = GetProcAddress( kernel,
                                                        "ExitProcess" ) ;
        if ( exit_proc == NULL ) {
            throw last_api_error( "GetProcAddress() failed" ) ;
        }
        unsigned            dummy = 0 ;
        // Note: the intermediate cast to void * is to silence Visual C++
        //       C4191, which is a useful warning to have.
        // -------------------------------------------------------------------
        process_private::handle const
                            h( CreateRemoteThread(
                                    m_impl->m_info.hProcess, nullptr, 0,
                                     reinterpret_cast< LPTHREAD_START_ROUTINE >(
                                          reinterpret_cast< void * >( exit_proc ) ),
                                     &dummy, 0, nullptr ) ) ;
        if ( h.get() == NULL ) {
            throw last_api_error( "CreateRemoteThread() failed" ) ;
        }
    }
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
