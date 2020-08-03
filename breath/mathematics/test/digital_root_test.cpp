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

#include "breath/mathematics/digital_root.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>

int                 test_digital_root() ;

namespace {

template< typename T >
int
trivial_digital_root( T n, int base )
{
    T                   sum = 0 ;
    while ( n != 0 ) {
        sum += ( n % base ) ;
        n /= base ;
    }

    return sum < base
               ? sum
               : trivial_digital_root( sum, base ) ;
}

void
check()
{
    for ( int n = 0 ; n < ( 10 * 1000 ) ; ++ n ) {
        //      Note that there's no hard maximum for the base as far as
        //      digital_root() is concerned. But, in practice, you'll
        //      run out of symbols if you want e.g. to represent a
        //      number in base 5000 :-) So we choose 128, here, as the
        //      maximum base to test.
        // -------------------------------------------------------------------
        int const           min_base = 2 ;
        int const           max_base = 128 ;
        for ( int base = min_base ; base <= max_base ; ++ base ) {
            BREATH_CHECK( breath::digital_root( n, base ) ==
                          trivial_digital_root( n, base ) ) ;
        }
    }
}

}

int
test_digital_root()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( "digital_root()", { check } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
