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
#include <ostream>

namespace {

template< typename T >
T
trivial_digital_root( T n, T base )
{
    T                   sum = 0 ;
    do {
        sum += ( n % base ) ;
        n /= base ;
    } while ( n != 0 ) ;

    if ( sum >= base ) {
        return trivial_digital_root( sum, base ) ;
    }

    return sum ;
}

void
check()
{
    for ( int n = 0 ; n < ( 10 * 1000 ) ; ++ n ) {
        int                 min_base = 3 ;
        int                 max_base = 36 ;
        for ( int base = min_base ; base <= max_base ; ++ base ) {
            BREATH_CHECK( breath::digital_root( n, base ) ==
                          trivial_digital_root( n, base ) ) ;
        }
    }
}

}

int
main()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { check } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
