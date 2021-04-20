// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2006-2007 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/environment/get_environment_variable.hpp"
#include "breeze/vocabulary/maybe.hpp"

#include <cstdlib>

namespace breeze_ns {

maybe< std::string >
get_environment_variable( std::string const & name )
{
    typedef maybe< std::string >
                        maybe_type ;

    char const * const  p = std::getenv( name.c_str() ) ;

    return p == nullptr
        ? maybe_type()
        : maybe_type( std::string( p ) )
        ;
}

}
