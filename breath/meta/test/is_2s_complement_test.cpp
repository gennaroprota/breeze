// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/meta/is_2s_complement.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>

int                 test_is_2s_complement() ;

using breath::meta::is_2s_complement ;

namespace {

//      This is actually a compile-time test. But we turn it into a
//      runtime test, at least for now, so that we get a report.
// ---------------------------------------------------------------------------
void
do_test()
{
    using breath::meta::is_2s_complement ;

    static_assert( ! is_2s_complement< bool >(),          "" ) ;
    static_assert(   is_2s_complement< signed char >(),   "" ) ;
    static_assert( ! is_2s_complement< unsigned char >(), "" ) ;

    static_assert(   is_2s_complement< int >(),           "" ) ;
    static_assert( ! is_2s_complement< unsigned int >(),  "" ) ;
}

}

int
test_is_2s_complement()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run(
             "is_2s_complement()",
             { do_test } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
