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

#include "breath/mathematics/gcd.hpp"
#include "breath/testing/testing.hpp"
#include <climits>
#include <iostream>

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
        {  3, -3, 3 }
    } ;

    for ( auto const & t : table ) {
        BREATH_CHECK( breath::gcd( t.a, t.b ) == t.gcd ) ;
        BREATH_CHECK( breath::gcd( t.b, t.a ) == t.gcd ) ;
    }
}

void
check_mixed_types()
{
    {
        signed char const   a = -80 ;
        unsigned int const  b = 32768 ;

        BREATH_CHECK( breath::gcd( a, b ) == 16 ) ;
        BREATH_CHECK( breath::gcd( b, a ) == 16 ) ;
    }

    {
        signed short const  a = -128 ;
        unsigned long long const
                            b = ULLONG_MAX ;
        BREATH_CHECK( breath::gcd( a, b ) == 1 ) ;
        BREATH_CHECK( breath::gcd( b, a ) == 1 ) ;
    }

    {
        int const           a = - INT_MAX ;
        unsigned int const  b =   INT_MAX ;

        BREATH_CHECK( breath::gcd( a, b ) == INT_MAX ) ;
        BREATH_CHECK( breath::gcd( b, a ) == INT_MAX ) ;
    }

    //      Other two cases which can be tricky for the implementation,
    //      because a % b is not zero. See:
    //
    //        <https://gcc.gnu.org/bugzilla/show_bug.cgi?id=92978>.
    // -----------------------------------------------------------------------
    {
        int const           a = -120 ;
        unsigned int const  b = 10 ;

        BREATH_CHECK( breath::gcd( a, b ) == 10 ) ;
        BREATH_CHECK( breath::gcd( b, a ) == 10 ) ;
    }
    {
        unsigned int const  a = 120 ;
        int const           b = -10 ;

        BREATH_CHECK( breath::gcd( a, b ) == 10 ) ;
        BREATH_CHECK( breath::gcd( b, a ) == 10 ) ;
    }
}

void
check_constexpr()
{
    constexpr int       n = breath::gcd( 10, 14 ) ;
    int                 array[ n ] ;
    static_cast< void >( array ) ;
}

}

int
main()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { check_int,
                                          check_mixed_types,
                                          check_constexpr } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
