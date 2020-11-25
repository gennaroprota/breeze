// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2008-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/testing/testing.hpp"
#include "breeze/text/set_of_chars.hpp"
#include "breeze/text/trim_tail.hpp"

int                 test_trim_tail() ;

namespace {

void
do_test()
{
    using breeze::trim_tail ;
    using breeze::set_of_chars ;

    BREEZE_CHECK( trim_tail( "" ) == "" ) ;
    BREEZE_CHECK( trim_tail( " " ) == "" ) ;
    BREEZE_CHECK( trim_tail( "\t" ) == "" ) ;
    BREEZE_CHECK( trim_tail( " \t" ) == "" ) ;
    BREEZE_CHECK( trim_tail( "\t " ) == "" ) ;

    BREEZE_CHECK( trim_tail( "abc  " ) == "abc" ) ;
    BREEZE_CHECK( trim_tail( "abc \t" ) == "abc" ) ;
    BREEZE_CHECK( trim_tail( "abc a" ) == "abc a" ) ;

    BREEZE_CHECK( trim_tail( "abcd", set_of_chars( "db" ) ) == "abc" ) ;
    BREEZE_CHECK( trim_tail( "abcd", set_of_chars( "badc" ) ) == "" ) ;
    BREEZE_CHECK( trim_tail( "a", set_of_chars( "bcde" ) ) == "a" ) ;
    BREEZE_CHECK( trim_tail( "abcd", set_of_chars( "bce" ) ) == "abcd" ) ;
}

}

int
test_trim_tail()
{
    using namespace breeze ;

    return test_runner::instance().run(
             "trim_tail()",
             { do_test } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
