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

#include "breath/text/to_uppercase.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>
#include <ostream>

int                 test_to_uppercase() ;

namespace {

void
do_tests()
{
    using breath::to_uppercase ;

    BREATH_CHECK( to_uppercase( "" ) == "" ) ;
    BREATH_CHECK( to_uppercase( "ABCD" ) == "ABCD" ) ;
    BREATH_CHECK( to_uppercase( "AbCd" ) == "ABCD" ) ;
    BREATH_CHECK( to_uppercase( "abcd" ) == "ABCD" ) ;
    BREATH_CHECK( to_uppercase( "a1" ) == "A1" ) ;
}

}

int
test_to_uppercase()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { do_tests } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
