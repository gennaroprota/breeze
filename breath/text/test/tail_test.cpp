// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/text/tail.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>

int                 test_tail() ;

namespace {

void
do_tests()
{
    BREATH_CHECK( breath::tail( "", 0   ) == "" ) ;
    BREATH_CHECK( breath::tail( "", 1   ) == "" ) ;
    BREATH_CHECK( breath::tail( "", 100 ) == "" ) ;

    BREATH_CHECK( breath::tail( "hello", 0   ) == "" ) ;
    BREATH_CHECK( breath::tail( "hello", 2   ) == "lo" ) ;
    BREATH_CHECK( breath::tail( "hello", 5   ) == "hello" ) ;
    BREATH_CHECK( breath::tail( "hello", 6   ) == "hello" ) ;
    BREATH_CHECK( breath::tail( "hello", 100 ) == "hello" ) ;
}

}

int
test_tail()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( "tail()", { do_tests } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
