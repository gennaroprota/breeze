// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/text/replace_all.hpp"
#include "breeze/testing/testing.hpp"
#include <string>

int                 test_replace_all() ;

namespace {

void do_tests()
{
    // No replacement should occur in an empty string
    {
        std::string test ;
        breeze::replace_all( test, "ab", "" ) ;
        BREEZE_CHECK( test == "" ) ;
    }

    // No replacement should occur in an empty string
    {
        std::string test ;
        breeze::replace_all( test, "ab", "xy" ) ;
        BREEZE_CHECK( test == "" ) ;
    }

    // Test a real replacement (with one occurrence)
    {
        std::string test( "test" ) ;
        breeze::replace_all( test, "e", "oa" ) ;
        BREEZE_CHECK( test == "toast" ) ;
    }

    // Test real replacements (one of which at the end)
    {
        std::string test( "provapro" ) ;
        breeze::replace_all( test, "pro", "i" ) ;
        BREEZE_CHECK( test == "ivai" ) ;

        breeze::replace_all( test, "va", "x" ) ;
        BREEZE_CHECK( test == "ixi" ) ;
    }

    // Test when 'from' is a substring of 'to'
    {
        std::string test( "provapro" ) ;
        breeze::replace_all( test, "prova", "provato" ) ;
        BREEZE_CHECK( test == "provatopro" ) ;
    }
    {
        std::string test( "provapro" ) ;
        breeze::replace_all( test, "prova", "approva") ;
        BREEZE_CHECK( test == "approvapro") ;
    }
    {
        std::string test( "prova" ) ;
        breeze::replace_all( test, "prova", "provato" ) ;
        BREEZE_CHECK( test == "provato" ) ;
    }
    {
        std::string test( "prova" ) ;
        breeze::replace_all( test, "prova", "approva" ) ;
        BREEZE_CHECK( test == "approva" ) ;
    }
}

void
empty_from_string_causes_assert()
{
    std::string         source( "foo" ) ;
    BREEZE_CHECK_THROWS( breeze::assert_failure,
        breeze::replace_all( source, "", "bar" ) ) ;
}

void
whole_string_can_be_replaced()
{
    std::string         source( "foo" ) ;
    breeze::replace_all( source, "foo", "abcdefgh" ) ;
    BREEZE_CHECK( source == "abcdefgh" ) ;

    breeze::replace_all( source, "abcdefgh", "" ) ;
    BREEZE_CHECK( source.empty() ) ;
}

}

int
test_replace_all()
{
    return breeze::test_runner::instance().run(
        "replace_all()",
        { do_tests,

          empty_from_string_causes_assert,
          whole_string_can_be_replaced } ) ;
}
