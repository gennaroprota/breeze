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

#include "breeze/preprocessing/prevent_macro_expansion.hpp"
#include "breeze/preprocessing/stringize_after_expansion.hpp"
#include "breeze/testing/testing.hpp"

#define foo( a )    unexisting_function( a )

int                 test_breeze_prevent_macro_expansion() ;

namespace {

void
(foo)( int )
{
    //      Make a dummy use of the foo() macro, to avoid a
    //      -Wunused-macros warning with Clang.
    // -----------------------------------------------------------------------
    char const *        dummy = BREEZE_STRINGIZE_AFTER_EXPANSION( foo( 1 ) ) ;
    static_cast< void >( dummy ) ;
}

//      This is actually a compile-time test: if the file compiles, then
//      everything is OK. But we turn it into a runtime test, at least
//      for now, so that we get a report.
// ---------------------------------------------------------------------------
void
do_test()
{
    foo BREEZE_PREVENT_MACRO_EXPANSION ( 1 ) ;
}

}

int
test_breeze_prevent_macro_expansion()
{
    return breeze::test_runner::instance().run(
             "BREEZE_PREVENT_MACRO_EXPANSION",
             { do_test } ) ;
}
