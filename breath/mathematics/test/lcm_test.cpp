// =========================================================================
//                This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/mathematics/lcm.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>

namespace {

void
do_check()
{
    constexpr struct
    {
        int a ;
        int b ;
        int lcm ;
    }                   table[] = {
        {  0,  0,  0 },
        { -1,  0,  0 },
        { -3,  0,  0 },
        {  18, 24, 72 },
        { -12, 10, 60 },
        {  12,-10, 60 },
        { -12,-10, 60 },
        { 23 * 5, 12 * 5, 23 * 12 * 5 },
        { 31 * 7, 7 * 2,  31 * 7 * 2 }
    } ;

    for ( auto const & t : table ) {
        BREATH_CHECK( breath::lcm( t.a, t.b ) == t.lcm ) ;
        BREATH_CHECK( breath::lcm( t.b, t.a ) == t.lcm ) ;
    }
}

}

int
main()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { do_check } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
