// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/mathematics/gcd.hpp"
#include "breeze/testing/testing.hpp"
#include <climits>

int                 test_gcd() ;

namespace {

void
check_int()
{
    struct
    {
        int a ;
        int b ;
        int gcd ;
    } const             table[] = {
        {  0,  0, 0 },
        { -1, -1, 1 },
        { -1,  1, 1 },
        {  1,  1, 1 },
        { 12,  4, 4 },
        { 36, 24, 12},
        { 30,-25, 5 },
        { -3,  0, 3 },
        {  3, -3, 3 },
        { INT_MIN, -1, 1 },
        { INT_MIN, -256, 256 },           // assuming 2's complement
        { INT_MAX, -1,   1 },
        { INT_MAX, INT_MIN + 1, INT_MAX } // assuming 2's complement
    } ;

    for ( auto const & t : table ) {
        BREEZE_CHECK( breeze::gcd( t.a, t.b ) == t.gcd ) ;
        BREEZE_CHECK( breeze::gcd( t.b, t.a ) == t.gcd ) ;
    }
}

void check_unsigned_int()
{
    struct
    {
        unsigned int a ;
        unsigned int b ;
        unsigned int gcd ;
    } const             table[] = {
        {  0,  0, 0 },
        {  1,  1, 1 },
        { 20,  4, 4 },
        { 72, 40, 8 },
        { UINT_MAX, UINT_MAX, UINT_MAX },
        { UINT_MAX, 0, UINT_MAX }
    } ;

    for ( auto const & t : table ) {
        BREEZE_CHECK( breeze::gcd( t.a, t.b ) == t.gcd ) ;
        BREEZE_CHECK( breeze::gcd( t.b, t.a ) == t.gcd ) ;
    }
}

void
check_constexpr()
{
    constexpr int       n = breeze::gcd( 10, 14 ) ;
    int                 array[ n ] = {} ;
    static_cast< void >( array ) ;
}

}

int
test_gcd()
{
    return breeze::test_runner::instance().run( "gcd()", { check_int,
                                                   check_unsigned_int,
                                                   check_constexpr } ) ;
}
