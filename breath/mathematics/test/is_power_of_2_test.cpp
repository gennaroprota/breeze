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

#include <limits>

int                 test_is_power_of_2() ;

namespace {

template< typename T >
void
do_check()
{
    T const             min = std::numeric_limits< T >::min() ;
    T const             max = std::numeric_limits< T >::max() ;

    BREATH_CHECK( ! breath::is_power_of_2( min ) ) ;

    for ( T i = min ; i < 0 ; i /= 2 ) {
        BREATH_CHECK( ! breath::is_power_of_2( i ) ) ;
    }

    BREATH_CHECK( ! breath::is_power_of_2( 0 ) ) ;
    BREATH_CHECK( breath::is_power_of_2( 1 ) ) ;

    for ( T i = max / 2 + 1 ; i > 1 ; i /= 2 ) {
        BREATH_CHECK( breath::is_power_of_2( i ) ) ;
        if (i != 2) {
            BREATH_CHECK( ! breath::is_power_of_2( i - 1 ) );
        }
        BREATH_CHECK( ! breath::is_power_of_2( i + 1 ) ) ;
    }
    BREATH_CHECK( ! breath::is_power_of_2( max ) ) ;
}

}

int
test_is_power_of_2()
{
    using namespace breath ;

    return test_runner::instance().run( "is_power_of_2()",
        { do_check< short >,
          do_check< unsigned short >,
          do_check< int >,
          do_check< unsigned >,
          do_check< long >,
          do_check< unsigned long > } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
