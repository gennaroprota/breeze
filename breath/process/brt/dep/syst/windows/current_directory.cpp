// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2015-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/process/current_directory.hpp"
#include "breath/diagnostics/last_api_error.hpp"
#include "breath/diagnostics/assert.hpp"
#include <Windows.h>

namespace breath {

std::string
current_directory()
{
    DWORD const         required = GetCurrentDirectoryA( 0, nullptr ) ;
    if ( required == 0 ) {
        throw last_api_error( "GetCurrentDirectory( 0, nullptr ) failed" ) ;
    }
    // assumes contiguity of std::string, as required by C++11
    std::string         s( required, '\0' ) ;
    if ( GetCurrentDirectoryA( required, &s[ 0 ] ) == 0 ) {
        throw last_api_error( "GetCurrentDirectory() failed" ) ;
    }
    s.resize( s.size() - 1 ) ; // remove trailing '\0'
    return s ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
