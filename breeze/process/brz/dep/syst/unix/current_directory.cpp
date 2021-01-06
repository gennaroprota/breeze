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
#include "breeze/diagnostics/assert.hpp"
#include "breeze/diagnostics/last_api_error.hpp"
#include "breeze/memory/auto_array.hpp"
#include <unistd.h>
#include <cerrno>
#include <cstddef>
#include <string>

namespace breeze_ns {

std::string
current_directory()
{
    std::ptrdiff_t      sz = 1024 ;
    auto_array< char >  aa ;

    char const *        p = nullptr ;
    do {
        aa.reset( new char[ sz ] ) ;
        p = getcwd( aa.raw_pointer(), sz ) ;
        sz *= 2 ;
    } while ( p == nullptr && errno == ERANGE ) ;

    if ( p == nullptr ) {
        throw last_api_error( "getcwd() failed" ) ;
    }
    return std::string( p ) ;
}

}
