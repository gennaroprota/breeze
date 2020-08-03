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

#include "breath/text/to_string.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>

int                 test_to_string() ;

namespace {

void do_tests()
{
    BREATH_CHECK( breath::to_string( 12 ) == "12" ) ;
    BREATH_CHECK( breath::to_string( " hello, world " ) == " hello, world " ) ;
    BREATH_CHECK( breath::to_string( "" ) == "" ) ;
    BREATH_CHECK( breath::to_string( 'a' ) == "a" ) ;

    //      Conversion from double. Note that these are not the same
    //      results as std::to_string().
    // -----------------------------------------------------------------------
    BREATH_CHECK( breath::to_string( 12.34 ) == "12.34" ) ;
    BREATH_CHECK( breath::to_string( 1e-10 ) == "1e-10" ) ;
    BREATH_CHECK( breath::to_string( 1e+50 ) == "1e+50" ) ;
    BREATH_CHECK( breath::to_string( 1e-50 ) == "1e-50" ) ;
    BREATH_CHECK( breath::to_string( 123456789.0 ) == "1.23457e+08" ) ;
}

}

int
test_to_string()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( "to_string()", { do_tests } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
