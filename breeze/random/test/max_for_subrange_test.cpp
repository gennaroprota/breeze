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

#include "breeze/random/max_for_subrange.hpp"
#include "breeze/testing/testing.hpp"
#include <climits>

int                 test_max_for_subrange() ;

namespace {

void
do_test()
{
    static struct
    {
        int x ;
        int m ;
        int result ;
    } const             values[] = {
        {   5,   32767,   32765 },
        {   5,     255,     251 },
        {   1,     255,     255 },
        {   0,     255,     255 },
        { 200,     300,     200 },
        { 255, INT_MAX, INT_MAX }
    };
    for ( auto const elem : values ) {
        BREEZE_CHECK( breeze::max_for_subrange( elem.x, elem.m ) ==
            elem.result ) ;
    }
}

}

int
test_max_for_subrange()
{
    return breeze::test_runner::instance().run(
        "max_for_subrange()",
        { do_test } ) ;

}
