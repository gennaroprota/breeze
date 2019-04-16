// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2018-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/mathematics/representation_in_base.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>
#include <ostream>

namespace {

void check()
{
    BREATH_CHECK( breath::representation_in_base( 64, 16 ) == "40" ) ;
    BREATH_CHECK( breath::representation_in_base( 169, 16 ) == "a9" ) ;
    BREATH_CHECK( breath::representation_in_base( 254, 2 ) == "11111110" ) ;
}

}

int
main()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { check } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
