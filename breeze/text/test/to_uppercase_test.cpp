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

#include "breeze/text/to_uppercase.hpp"
#include "breeze/testing/testing.hpp"

int                 test_to_uppercase() ;

namespace {

void
do_tests()
{
    using breeze::to_uppercase ;

    BREEZE_CHECK( to_uppercase( "" ) == "" ) ;
    BREEZE_CHECK( to_uppercase( "ABCD" ) == "ABCD" ) ;
    BREEZE_CHECK( to_uppercase( "AbCd" ) == "ABCD" ) ;
    BREEZE_CHECK( to_uppercase( "abcd" ) == "ABCD" ) ;
    BREEZE_CHECK( to_uppercase( "a1" ) == "A1" ) ;
}

}

int
test_to_uppercase()
{
    return breeze::test_runner::instance().run( "to_uppercase()",
        { do_tests } ) ;
}
