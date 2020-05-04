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

#include "breath/mathematics/count_bits.hpp"
#include "breath/testing/testing.hpp"
#include <climits>
#include <cstddef>
#include <iostream>
#include <ostream>

namespace {

template< typename T >
int
trivially_count_bits( T t )
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
    BREATH_CHECK( breath::count_bits( false ) == 0 ) ;
    BREATH_CHECK( breath::count_bits( true ) == 1 ) ;
    for ( unsigned i = 0 ; i <= UCHAR_MAX ; ++ i ) {
        BREATH_CHECK( breath::count_bits( i ) == trivially_count_bits( i ) ) ;
        BREATH_CHECK( breath::count_bits( static_cast< unsigned char >( i ) ) ==
                          trivially_count_bits( i ) ) ;
    }
}

void check2()
{
    unsigned long       n = 0b010'110'011'011 ;
    BREATH_CHECK( breath::count_bits( n ) == 7 ) ;

    n = 0b11'010'110'011'011 ;
    BREATH_CHECK( breath::count_bits( n ) == 9 ) ;
}

}

int
main()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { check, check2 } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
