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

#include "breeze/mathematics/population_count.hpp"
#include "breeze/testing/testing.hpp"
#include <climits>
#include <cstddef>

int                 test_population_count() ;

namespace {

template< typename T >
int
trivially_count_one_bits( T t )
{
    int                 count = 0 ;
    while ( t != 0 ) {
        ++ count ;
        t &= ( t - 1 ) ;
    }
    return count ;
}

void check()
{
    for ( unsigned i = 0 ; i <= UCHAR_MAX ; ++ i ) {
        BREEZE_CHECK( breeze::population_count( i ) ==
                      trivially_count_one_bits( i ) ) ;
        BREEZE_CHECK( breeze::population_count(
                            static_cast< unsigned char >( i ) ) ==
                      trivially_count_one_bits( i ) ) ;
    }
}

void check2()
{
    unsigned long       n = 0b010'110'011'011 ;
    BREEZE_CHECK( breeze::population_count( n ) == 7 ) ;

    n = 0b11'010'110'011'011 ;
    BREEZE_CHECK( breeze::population_count( n ) == 9 ) ;
}

}

int
test_population_count()
{
    return breeze::test_runner::instance().run(
        "population_count()",
        { check,
          check2 } ) ;
}
