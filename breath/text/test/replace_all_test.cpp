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

#include "breath/text/replace_all.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>
#include <ostream>
#include <string>

namespace {

void do_tests()
{
    // No replacement should occur in an empty string
    {
        std::string test ;
        breath::replace_all( test, "ab", "" ) ;
        BREATH_CHECK( test == "" ) ;
    }

    // No replacement should occur in an empty string
    {
        std::string test ;
        breath::replace_all( test, "ab", "xy" ) ;
        BREATH_CHECK( test == "" ) ;
    }

    // Test a real replacement (with one occurrence)
    {
        std::string test( "test" ) ;
        breath::replace_all( test, "e", "oa" ) ;
        BREATH_CHECK( test == "toast" ) ;
    }

    // Test real replacements (one of which at the end)
    {
        std::string test( "provapro" ) ;
        breath::replace_all( test, "pro", "i" ) ;
        BREATH_CHECK( test == "ivai" ) ;

        breath::replace_all( test, "va", "x" ) ;
        BREATH_CHECK( test == "ixi" ) ;
    }

    // Test when 'from' is a substring of 'to'
    {
        std::string test( "provapro" ) ;
        breath::replace_all( test, "prova", "provato" ) ;
        BREATH_CHECK( test == "provatopro" ) ;
    }
    {
        std::string test( "provapro" ) ;
        breath::replace_all( test, "prova", "approva") ;
        BREATH_CHECK( test == "approvapro") ;
    }
    {
        std::string test( "prova" ) ;
        breath::replace_all( test, "prova", "provato" ) ;
        BREATH_CHECK( test == "provato" ) ;
    }
    {
        std::string test( "prova" ) ;
        breath::replace_all( test, "prova", "approva" ) ;
        BREATH_CHECK( test == "approva" ) ;
    }
}

}

int
main()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { do_tests } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
