// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/text/tail.hpp"
#include "breeze/testing/testing.hpp"

int                 test_tail() ;

namespace {

void
do_tests()
{
    BREEZE_CHECK( breeze::tail( "", 0   ) == "" ) ;
    BREEZE_CHECK( breeze::tail( "", 1   ) == "" ) ;
    BREEZE_CHECK( breeze::tail( "", 100 ) == "" ) ;

    BREEZE_CHECK( breeze::tail( "hello", 0   ) == "" ) ;
    BREEZE_CHECK( breeze::tail( "hello", 2   ) == "lo" ) ;
    BREEZE_CHECK( breeze::tail( "hello", 5   ) == "hello" ) ;
    BREEZE_CHECK( breeze::tail( "hello", 6   ) == "hello" ) ;
    BREEZE_CHECK( breeze::tail( "hello", 100 ) == "hello" ) ;
}

}

int
test_tail()
{
    return breeze::test_runner::instance().run(
        "tail()",
        { do_tests } ) ;
}
