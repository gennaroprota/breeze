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
        std::string const   test ;
        std::string const   result = breeze::replace_all( test, "ab", "" ) ;
        BREEZE_CHECK( result.empty() ) ;
    }

    // No replacement should occur in an empty string
    {
        std::string const   test ;
        std::string const result = breeze::replace_all( test, "ab", "xy" ) ;
        BREEZE_CHECK( result.empty() ) ;
    }

    // Test a real replacement (with one occurrence)
    {
        std::string const   test( "test" ) ;
        std::string const   result = breeze::replace_all( test, "e", "oa" ) ;
        BREEZE_CHECK( result == "toast" ) ;
    }

    // Test real replacements (one of which at the end)
    {
        std::string const   test( "provapro" ) ;
        std::string         result = breeze::replace_all( test, "pro", "i" ) ;
        BREEZE_CHECK( result == "ivai" ) ;

        result = breeze::replace_all( result, "va", "x" ) ;
        BREEZE_CHECK( result == "ixi" ) ;
    }

    // Test when 'from' is a substring of 'to'
    {
        std::string const   test( "provapro" ) ;
        std::string const   result = breeze::replace_all(
            test, "prova", "provato" ) ;
        BREEZE_CHECK( result == "provatopro" ) ;
    }
    {
        std::string const   test( "provapro" ) ;
        std::string const   result = breeze::replace_all(
            test, "prova", "approva") ;
        BREEZE_CHECK( result == "approvapro") ;
    }
    {
        std::string const   test( "prova" ) ;
        std::string const   result = breeze::replace_all(
            test, "prova", "provato" ) ;
        BREEZE_CHECK( result == "provato" ) ;
    }
    {
        std::string const   test( "prova" ) ;
        std::string const   result = breeze::replace_all(
            test, "prova", "approva" ) ;
        BREEZE_CHECK( result == "approva" ) ;
    }
}

void
empty_from_string_causes_assert()
{
    std::string         test( "foo" ) ;
    BREEZE_CHECK_THROWS( breeze::assert_failure,
        breeze::replace_all( test, "", "bar" ) ) ;
}

void
whole_string_can_be_replaced()
{
    std::string const   test( "foo" ) ;
    std::string         result = breeze::replace_all(
        test, "foo", "abcdefgh" ) ;
    BREEZE_CHECK( result == "abcdefgh" ) ;

    result = breeze::replace_all( result, "abcdefgh", "" ) ;
    BREEZE_CHECK( result.empty() ) ;
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
