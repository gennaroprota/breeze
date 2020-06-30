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

#include "breath/environment/get_environment_variable.hpp"
#include "breath/idiom/maybe.hpp"

#include <cstdlib>

namespace breath_ns {

maybe< std::string >
get_environment_variable( std::string const & name )
{
    typedef maybe< std::string >
                        maybe_type ;

    char const * const  p( std::getenv( name.c_str() ) ) ;

    return p == nullptr
        ? maybe_type()
        : maybe_type( std::string( p ) )
        ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
