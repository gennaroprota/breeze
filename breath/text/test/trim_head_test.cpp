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
#include "breath/text/set_of_chars.hpp"
#include "breath/text/trim_head.hpp"
#include <iostream>

int                 test_trim_head() ;

namespace {

void
do_test()
{
    using breath::trim_head ;
    using breath::set_of_chars ;

    BREATH_CHECK( trim_head( "" ) == "" ) ;
    BREATH_CHECK( trim_head( " " ) == "" ) ;
    BREATH_CHECK( trim_head( "\t" ) == "" ) ;
    BREATH_CHECK( trim_head( " \t" ) == "" ) ;
    BREATH_CHECK( trim_head( "\t " ) == "" ) ;

    BREATH_CHECK( trim_head( "  abc" ) == "abc" ) ;
    BREATH_CHECK( trim_head( "\t abc" ) == "abc" ) ;
    BREATH_CHECK( trim_head( "abc a" ) == "abc a" ) ;

    BREATH_CHECK( trim_head( "abcd", set_of_chars( "ab" ) ) == "cd" ) ;
    BREATH_CHECK( trim_head( "abcde", set_of_chars( "badc" ) ) == "e" ) ;
    BREATH_CHECK( trim_head( "a", set_of_chars( "bcde" ) ) == "a" ) ;
    BREATH_CHECK( trim_head( "abcd", set_of_chars( "bce" ) ) == "abcd" ) ;
}

}

int
test_trim_head()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run(
             "trim_head()",
             { do_test } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
