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

#include "breath/testing/testing.hpp"
#include "breath/text/begins_with.hpp"
#include <cstddef>
#include <iostream>
#include <string>

int                 test_begins_with() ;

namespace {

void
do_test()
{
    using breath::begins_with ;

    std::string const   empty ;
    BREATH_CHECK( begins_with( empty, empty ) ) ;

    BREATH_CHECK(   begins_with( "",  ""  ) ) ;
    BREATH_CHECK(   begins_with( "a", ""  ) ) ;
    BREATH_CHECK(   begins_with( "a", "a" ) ) ;
    BREATH_CHECK( ! begins_with( "",  "a" ) ) ;
    BREATH_CHECK( ! begins_with( "a", "ab" ) ) ;

    // some space tests
    BREATH_CHECK(   begins_with( " a",  " "   ) ) ;
    BREATH_CHECK(   begins_with( " a  ", " "   ) ) ;
    BREATH_CHECK(   begins_with( "  a", "  "  ) ) ;
    BREATH_CHECK( ! begins_with( " a",  "  "  ) ) ;
    BREATH_CHECK( ! begins_with( " a",  "a"   ) ) ;
    BREATH_CHECK( ! begins_with( "          ", "\t" ) ) ;

    BREATH_CHECK(   begins_with( "abc", "ab"   ) ) ;
    BREATH_CHECK( ! begins_with( "ab", "abc"   ) ) ;
    BREATH_CHECK( ! begins_with( "bcd", "abcd" ) ) ;

    // check that embedded NULs are handled correctly
    std::string         s ;
    s.push_back( 'a' ) ;
    s.push_back( '\0' ) ;
    s.push_back( 'b' ) ;

    std::string         t ;
    t.push_back( '\0' ) ;
    BREATH_CHECK( ! begins_with( s, t) ) ;
    t = "a" ;
    t.push_back( '\0' ) ;
    BREATH_CHECK( begins_with( s, t ) ) ;
    BREATH_CHECK( begins_with( s, s ) ) ;
    BREATH_CHECK( begins_with( t, t ) ) ;
}

}

int
test_begins_with()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run(
             "begins_with()",
             { do_test } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
