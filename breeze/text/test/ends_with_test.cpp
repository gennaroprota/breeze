// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/testing/testing.hpp"
#include "breeze/text/ends_with.hpp"

#include <string>

int                 test_ends_with() ;

namespace {

void
do_test()
{
    using breeze::ends_with ;

    std::string const   empty ;
    BREEZE_CHECK( ends_with( empty, empty ) ) ;

    BREEZE_CHECK(   ends_with( "",  ""  ) ) ;
    BREEZE_CHECK(   ends_with( "a", ""  ) ) ;
    BREEZE_CHECK(   ends_with( "a", "a" ) ) ;
    BREEZE_CHECK( ! ends_with( "",  "a" ) ) ;
    BREEZE_CHECK( ! ends_with( "a", "ab" ) ) ;

    // some space tests
    BREEZE_CHECK(   ends_with( "a ",  " "   ) ) ;
    BREEZE_CHECK(   ends_with( "a  ", " "   ) ) ;
    BREEZE_CHECK(   ends_with( "a  ", "  "  ) ) ;
    BREEZE_CHECK( ! ends_with( "a ",  "  "  ) ) ;
    BREEZE_CHECK( ! ends_with( "a ",  "a"   ) ) ;
    BREEZE_CHECK( ! ends_with( "          ", "\t" ) ) ;

    BREEZE_CHECK(   ends_with( "abc", "bc"   ) ) ;
    BREEZE_CHECK( ! ends_with( "bcd", "abcd" ) ) ;

    // check that embedded NULs are handled correctly
    std::string         s ;
    s.push_back( 'a' ) ;
    s.push_back( '\0' ) ;
    s.push_back( 'b' ) ;

    std::string         t ;
    t.push_back( '\0' ) ;
    BREEZE_CHECK( ! ends_with( s, t) ) ;
    t.push_back( 'b' ) ;
    BREEZE_CHECK( ends_with( s, t ) ) ;
    BREEZE_CHECK( ends_with( s, s ) ) ;
    BREEZE_CHECK( ends_with( s, t ) ) ;
}

}

int
test_ends_with()
{
    return breeze::test_runner::instance().run(
             "ends_with()",
             { do_test } ) ;
}
