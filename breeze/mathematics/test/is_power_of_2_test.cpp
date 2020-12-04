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

#include "breeze/mathematics/is_power_of_2.hpp"
#include "breeze/testing/testing.hpp"

#include <limits>

int                 test_is_power_of_2() ;

namespace {

template< typename T >
void
do_check()
{
    T const             min = std::numeric_limits< T >::min() ;
    T const             max = std::numeric_limits< T >::max() ;

    BREEZE_CHECK( ! breeze::is_power_of_2( min ) ) ;

    for ( T i = min ; i < 0 ; i /= 2 ) {
        BREEZE_CHECK( ! breeze::is_power_of_2( i ) ) ;
    }

    BREEZE_CHECK( ! breeze::is_power_of_2( 0 ) ) ;
    BREEZE_CHECK( breeze::is_power_of_2( 1 ) ) ;

    for ( T i = max / 2 + 1 ; i > 1 ; i /= 2 ) {
        BREEZE_CHECK( breeze::is_power_of_2( i ) ) ;
        if (i != 2) {
            BREEZE_CHECK( ! breeze::is_power_of_2( i - 1 ) );
        }
        BREEZE_CHECK( ! breeze::is_power_of_2( i + 1 ) ) ;
    }
    BREEZE_CHECK( ! breeze::is_power_of_2( max ) ) ;
}

}

int
test_is_power_of_2()
{
    using namespace breeze ;

    return test_runner::instance().run( "is_power_of_2()",
        { do_check< short >,
          do_check< unsigned short >,
          do_check< int >,
          do_check< unsigned >,
          do_check< long >,
          do_check< unsigned long > } ) ;
}
