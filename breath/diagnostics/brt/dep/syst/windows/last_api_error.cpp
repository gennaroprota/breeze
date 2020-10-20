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

#include "breath/top_level_namespace.hpp"
#include <Windows.h>
#include <string>

namespace breath_ns {
namespace           {

std::string
format_message( char const * incipit, long long last_error )
{
    int const           max_size = 1024 ;
    std::string         s( max_size, '\0' ) ;
    DWORD const         ret = FormatMessageA(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        static_cast< DWORD >( last_error ),
        0,
        &s[ 0 ], // assumes contiguity of std::string
        max_size,
        nullptr
    ) ;

    if ( ret == 0 ) {
        s = "couldn't obtain the error description; see the error code, instead"
            ;
    } else {
        //      Strip the null character.
        // -------------------------------------------------------------------
        s.resize( ret ) ;

        //      Strip the trailing \r\n. (Could use remove_from_end().)
        // -------------------------------------------------------------------
        if ( ret > 2 && s[ ret - 2 ] == '\r' && s[ ret - 1 ] == '\n' ) {
            s.resize( ret - 2 ) ;
        }
    }

    return incipit != nullptr && incipit[ 0 ] != '\0'
        ? std::string( incipit ) + ": " + s
        : s
        ;
}

}

//      Possibly tricky point: format_message() calls the
//      FormatMessage() API, which may fail, altering GetLastError().
//      So, we can't do something like:
//
//      last_api_error::last_api_error( char const * p )
//          :   base_type( format_message( p ) ),
//              m_last_error( GetLastError() )
//      {
//          ...
//      }
//
//      because that could initialize m_last_error with the wrong value.
//
//      This is the reason why we forward to another (private)
//      constructor.
// ---------------------------------------------------------------------------
last_api_error::last_api_error( char const * p )
    :   last_api_error( p, GetLastError() )
{
}

last_api_error::last_api_error( last_api_error const & other ) noexcept
    :   base_type( other ), m_last_error( other.m_last_error )
{
}

last_api_error::~last_api_error() noexcept = default ;

last_api_error::last_api_error( char const * p, long long error_code )
    :   base_type( format_message( p, error_code ) ),
        m_last_error( error_code )
{
}

long long
last_api_error::code() const noexcept
{
    return m_last_error ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
