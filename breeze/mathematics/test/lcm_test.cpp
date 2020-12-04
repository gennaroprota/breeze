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

#include "breeze/mathematics/lcm.hpp"
#include "breeze/testing/testing.hpp"
#include <climits>

int                 test_lcm() ;

namespace {

void
check_int()
{
    struct
    {
        int a ;
        int b ;
        int lcm ;
    } const             table[] = {
        {  0,  0,  0 },
        { -1,  0,  0 },
        { -3,  0,  0 },
        {  18, 24, 72 },
        { -12, 10, 60 },
        {  12,-10, 60 },
        { -12,-10, 60 },
        { 23 * 5, 12 * 5, 23 * 12 * 5 },
        { 31 * 7, 7 * 2,  31 * 7 * 2 },
        { INT_MIN + 1, -1, INT_MAX },       // assuming 2's complement
        { INT_MIN + 1, INT_MAX, INT_MAX },  // assuming 2's complement

    } ;

    for ( auto const & t : table ) {
        BREEZE_CHECK( breeze::lcm( t.a, t.b ) == t.lcm ) ;
        BREEZE_CHECK( breeze::lcm( t.b, t.a ) == t.lcm ) ;
    }
}

void
check_unsigned_int()
{
    auto const          int_max = static_cast< unsigned int >( INT_MAX ) ;
    struct
    {
        unsigned int a ;
        unsigned int b ;
        unsigned int lcm ;
    } const             table[] = {
        {  0,  0,  0 },
        {  1,  0,  0 },
        {  3,  0,  0 },
        {  18, 24, 72 },
        { int_max + 1, 1, int_max + 1 },
        { int_max + 1, 0, 0 },
        { UINT_MAX, 0, 0 },
        { UINT_MAX, 1, UINT_MAX }
    } ;

    for ( auto const & t : table ) {
        BREEZE_CHECK( breeze::lcm( t.a, t.b ) == t.lcm ) ;
        BREEZE_CHECK( breeze::lcm( t.b, t.a ) == t.lcm ) ;
    }
}

void
check_constexpr()
{
    constexpr int       n = breeze::lcm( 10, 14 ) ;
    int                 array[ n ] = {} ;
    static_cast< void >( array ) ;
}

}

int
test_lcm()
{
    return breeze::test_runner::instance().run( "lcm()", { check_int,
                                                   check_unsigned_int,
                                                   check_constexpr } ) ;
}
