// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/mathematics/is_power_of_2.hpp"
#include "breath/testing/testing.hpp"

#include <climits>
#include <iostream>

int                 test_is_power_of_2() ;

namespace {

void
do_check()
{
    BREATH_CHECK( ! breath::is_power_of_2( INT_MIN ) ) ;

    for ( int i = INT_MIN ; i < 0 ; i /= 2 ) {
        BREATH_CHECK( ! breath::is_power_of_2( i ) ) ;
    }

    BREATH_CHECK( ! breath::is_power_of_2( 0 ) ) ;
    BREATH_CHECK( breath::is_power_of_2( 1 ) ) ;

    for ( int i = INT_MAX / 2 + 1 ; i > 1 ; i /= 2 ) {
        BREATH_CHECK( breath::is_power_of_2( i ) ) ;
        if (i != 2) {
            BREATH_CHECK( ! breath::is_power_of_2( i - 1 ) );
        }
        BREATH_CHECK( ! breath::is_power_of_2( i + 1 ) ) ;
    }
    BREATH_CHECK( ! breath::is_power_of_2( INT_MAX ) ) ;
}

}

int
test_is_power_of_2()
{
    using namespace breath ;

    return test_runner::instance().run( "is_power_of_2()", { do_check } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
