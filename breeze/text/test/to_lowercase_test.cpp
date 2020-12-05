// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/text/to_lowercase.hpp"
#include "breeze/testing/testing.hpp"

int                 test_to_lowercase() ;

namespace {

void
do_tests()
{
    using breeze::to_lowercase ;

    BREEZE_CHECK( to_lowercase( "" ) == "" ) ;
    BREEZE_CHECK( to_lowercase( "ABCD" ) == "abcd" ) ;
    BREEZE_CHECK( to_lowercase( "AbCd" ) == "abcd" ) ;
    BREEZE_CHECK( to_lowercase( "abcd" ) == "abcd" ) ;
    BREEZE_CHECK( to_lowercase( "A1" ) == "a1" ) ;
}

}

int
test_to_lowercase()
{
    return breeze::test_runner::instance().run(
        "to_lowercase()",
        { do_tests } ) ;
}
