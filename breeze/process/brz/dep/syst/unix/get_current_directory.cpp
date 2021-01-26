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
#include "breeze/memory/array_pointer.hpp"
#include <unistd.h>
#include <cerrno>
#include <cstddef>
#include <string>

namespace breeze_ns {

std::string
get_current_directory()
{
    std::ptrdiff_t      sz = 1024 ;
    array_pointer< char >  ap ;

    char const *        p = nullptr ;
    do {
        ap.reset( new char[ sz ] ) ;
        p = getcwd( ap.raw_pointer(), sz ) ;
        sz *= 2 ;
    } while ( p == nullptr && errno == ERANGE ) ;

    if ( p == nullptr ) {
        throw last_api_error( "getcwd() failed" ) ;
    }
    return std::string( p ) ;
}

}
