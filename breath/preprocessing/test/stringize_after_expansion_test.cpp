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

#include "breath/preprocessing/stringize_after_expansion.hpp"
#include "breath/testing/testing.hpp"
#include <cstring>
#include <iostream>
#include <ostream>

#define FOO 1
#define FOO2 FOO

#define BAR "a"
#define BAR2 BAR

#define FIRST_TOKEN multiple

int                 test_breath_stringize_after_expansion() ;

namespace {

void
do_tests()
{
    BREATH_CHECK( std::strcmp( BREATH_STRINGIZE_AFTER_EXPANSION( FOO2 ),
                               "1" )  == 0 ) ;
    BREATH_CHECK( std::strcmp( BREATH_STRINGIZE_AFTER_EXPANSION( BAR2 ),
                               "\"a\"" )  == 0 ) ;

    BREATH_CHECK( std::strcmp( BREATH_STRINGIZE_AFTER_EXPANSION( FIRST_TOKEN
                                                                 tokens),
                               "multiple tokens" ) == 0 ) ;
}

}

int
test_breath_stringize_after_expansion()
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
