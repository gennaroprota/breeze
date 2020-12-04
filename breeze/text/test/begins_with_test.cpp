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
#include "breeze/text/begins_with.hpp"
#include <cstddef>
#include <string>

int                 test_begins_with() ;

namespace {

void
do_test()
{
    using breeze::begins_with ;

    std::string const   empty ;
    BREEZE_CHECK( begins_with( empty, empty ) ) ;

    BREEZE_CHECK(   begins_with( "",  ""  ) ) ;
    BREEZE_CHECK(   begins_with( "a", ""  ) ) ;
    BREEZE_CHECK(   begins_with( "a", "a" ) ) ;
    BREEZE_CHECK( ! begins_with( "",  "a" ) ) ;
    BREEZE_CHECK( ! begins_with( "a", "ab" ) ) ;

    // some space tests
    BREEZE_CHECK(   begins_with( " a",  " "   ) ) ;
    BREEZE_CHECK(   begins_with( " a  ", " "   ) ) ;
    BREEZE_CHECK(   begins_with( "  a", "  "  ) ) ;
    BREEZE_CHECK( ! begins_with( " a",  "  "  ) ) ;
    BREEZE_CHECK( ! begins_with( " a",  "a"   ) ) ;
    BREEZE_CHECK( ! begins_with( "          ", "\t" ) ) ;

    BREEZE_CHECK(   begins_with( "abc", "ab"   ) ) ;
    BREEZE_CHECK( ! begins_with( "ab", "abc"   ) ) ;
    BREEZE_CHECK( ! begins_with( "bcd", "abcd" ) ) ;

    // check that embedded NULs are handled correctly
    std::string         s ;
    s.push_back( 'a' ) ;
    s.push_back( '\0' ) ;
    s.push_back( 'b' ) ;

    std::string         t ;
    t.push_back( '\0' ) ;
    BREEZE_CHECK( ! begins_with( s, t) ) ;
    t = "a" ;
    t.push_back( '\0' ) ;
    BREEZE_CHECK( begins_with( s, t ) ) ;
    BREEZE_CHECK( begins_with( s, s ) ) ;
    BREEZE_CHECK( begins_with( t, t ) ) ;
}

}

int
test_begins_with()
{
    using namespace breeze ;

    return test_runner::instance().run(
             "begins_with()",
             { do_test } ) ;
}
