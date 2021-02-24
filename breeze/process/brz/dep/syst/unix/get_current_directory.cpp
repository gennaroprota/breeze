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

#include "breeze/process/get_current_directory.hpp"
#include "breeze/diagnostics/last_api_error.hpp"
#include <unistd.h>
#include <cerrno>
#include <cstddef>
#include <cstring>
#include <string>

namespace breeze_ns {

std::string
get_current_directory()
{
    std::ptrdiff_t      sz = 1024 ;
    std::string         result ;

    char const *        p = nullptr ;
    do {
        result.resize( sz ) ;
        //      Note:
        //          this assumes contiguity of std::string, which is
        //          guaranteed starting from C++11.
        // -------------------------------------------------------------------
        p = getcwd( &result[ 0 ], sz ) ;
        sz *= 2 ;
    } while ( p == nullptr && errno == ERANGE ) ;

    if ( p == nullptr ) {
        throw last_api_error( "getcwd() failed" ) ;
    }

    result.resize( std::strlen( result.c_str() ) ) ;
    return result ;
}

}
