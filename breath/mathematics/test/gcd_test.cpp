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
#include <iostream>

namespace {

void
do_check()
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

    return test_runner::instance().run( { do_check, check_constexpr } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
