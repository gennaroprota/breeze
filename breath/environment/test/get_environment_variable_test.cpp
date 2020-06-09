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
#include <string>

/////////
#include "breath/diagnostics/assert.hpp"
#define DO_TEST( x ) BREATH_ASSERT( x )
//////

int                 test_get_environment_variable() ;

int
test_get_environment_variable()
{
    using namespace breath ;

    maybe< std::string > const
                        e = get_environment_variable( "BREATH_ROOT" ) ;

    DO_TEST( e.is_valid() ) ;
    DO_TEST( ! e.value().empty() ) ;

    return EXIT_SUCCESS ;
}
