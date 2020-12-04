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

#include "breeze/process/current_directory.hpp"
#include "breeze/diagnostics/last_api_error.hpp"
#include <Windows.h>

namespace breeze_ns {

std::string
current_directory()
{
    DWORD const         required = GetCurrentDirectoryA( 0, nullptr ) ;
    if ( required == 0 ) {
        throw last_api_error( "GetCurrentDirectory( 0, nullptr ) failed" ) ;
    }
    //      Note:
    //          this assumes contiguity of std::string, which is
    //          guaranteed starting from C++11.
    // -----------------------------------------------------------------------
    std::string         s( required, '\0' ) ;
    if ( GetCurrentDirectoryA( required, &s[ 0 ] ) == 0 ) {
        throw last_api_error( "GetCurrentDirectory() failed" ) ;
    }
    s.resize( s.size() - 1 ) ; // remove trailing '\0'
    return s ;
}

}
