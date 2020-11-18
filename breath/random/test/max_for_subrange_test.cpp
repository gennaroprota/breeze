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

#include "breath/random/max_for_subrange.hpp"
#include "breath/testing/testing.hpp"

int                 test_max_for_subrange() ;

namespace {

void
do_test()
{
    static struct {
        int m ;
        int x ;
        unsigned int result ;
    }                   values[] = {
        { 5, 32767, 32765 },
        { 5,   255,   251 },
        { 1,   255,   255 },
        { 0,   255,   255 }

    };
    for ( auto const elem : values ) {
        BREATH_CHECK( breath::max_for_subrange( elem.m, elem.x ) ==
            elem.result ) ;
    }
}

}

int
test_max_for_subrange()
{
    using namespace breath ;

    return test_runner::instance().run( "max_for_subrange()", { do_test } ) ;

}


// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
