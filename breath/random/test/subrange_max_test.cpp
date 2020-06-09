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

#include "breath/random/subrange_max.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>

int                 test_subrange_max() ;

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
    for ( auto elem : values ) {
        BREATH_CHECK( breath::subrange_max( elem.m, elem.x ) == elem.result ) ;
    }
}

}

int
test_subrange_max()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { do_test } ) ;

}


// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
