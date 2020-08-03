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

#include "breath/mathematics/clamp.hpp"
#include "breath/testing/testing.hpp"
#include <climits>
#include <cstddef>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int                 test_clamp() ;

namespace {

void
check()
{
    struct
    {
        int value ;
        int low ;
        int hi ;
        int result ;
    } const             table[] =
    {
        { 1, 5, 8, 5 },
        { 7, 5, 8, 7 },
        { 9, 5, 8, 8 },
        { 3, INT_MIN, INT_MIN, INT_MIN },
        { 1, INT_MIN, INT_MAX, 1 },
        { 5, INT_MAX, INT_MAX, INT_MAX },
        { 3, 3, 3, 3 }
    } ;

    for ( auto const & item : table ) {
        BREATH_CHECK( breath::clamp( item.value, item.low, item.hi )
                                                             == item.result ) ;
    }
}

void
check2()
{
    //      Check that a reference to the first argument is returned
    //      when the first argument is equivalent to one of the
    //      bounds.
    // -----------------------------------------------------------------------
    int const           a = 5 ;
    int const           low = 5 ;
    int const           high = 10 ;

    BREATH_CHECK( &breath::clamp( a, low, high ) == &a ) ;

    int const           a2 = 10 ;

    BREATH_CHECK( &breath::clamp( a2, low, high) == &a2 ) ;

    //      Check that a reference to the first argument is returned
    //      when the first argument is equivalent to *both* bounds.
    // -----------------------------------------------------------------------
    int const           b = 5 ;
    int const           low2 = 5 ;
    int const           high2 = 5 ;
    BREATH_CHECK( &breath::clamp( b, low2, high2 ) == &b ) ;
}

void
check3()
{
    //      An example taken from
    //        <https://github.com/sean-parent/sean-parent.github.io/wiki/presentations/2016-05-16-better-code/2016-05-16-better-code.pdf#page=27>
    // -----------------------------------------------------------------------
    using               pair = std::pair< int, std::string > ;
    pair                a  = { 1, "OK" } ;
    pair                lo = { 1, "FAIL: LO" } ;
    pair                hi = { 2, "FAIL: HI" } ;
    a = breath::clamp( a, lo, hi, []( auto const & x, auto const & y ) {
                            return x.first < y.first ;
                        } ) ;
    BREATH_CHECK( a.second == "OK" ) ;
}

}

int
test_clamp()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( "clamp()",
                                        { check, check2, check3 } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
