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

#include "breath/random/entropy_source.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>

int                 test_entropy_source() ;

namespace {

void
do_test()
{
    breath::entropy_source
                        source ;

    auto const          value = source.next() ;
    BREATH_CHECK( source.min() <= value &&
                    value <= source.max() ) ;

    int const           maximum = 15 ;
    auto const          capped_value = source( maximum ) ;
    BREATH_CHECK( source.min() <= capped_value &&
                    capped_value <= maximum ) ;

    BREATH_CHECK( source.release() ) ;

    //      Check that a second release doesn't yield "success".
    // -----------------------------------------------------------------------
    BREATH_CHECK( ! source.release() ) ;
}

}

int
test_entropy_source()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run(
             "entropy_source",
             { do_test } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
