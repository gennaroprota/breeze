// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2013 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/preprocessing/prevent_macro_expansion.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>

#define foo( a )    unexisting_function( a )

int                 test_breath_prevent_macro_expansion() ;

namespace {

void
(foo)( int )
{
}

//      This is actually a compile-time test: if the file compiles, then
//      everything is OK. But we turn it into a runtime test, at least
//      for now, so that we get a report.
// ---------------------------------------------------------------------------
void
do_test()
{
    foo BREATH_PREVENT_MACRO_EXPANSION ( 1 ) ;
}

}

int
test_breath_prevent_macro_expansion()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run(
             "BREATH_PREVENT_MACRO_EXPANSION",
             { do_test } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
