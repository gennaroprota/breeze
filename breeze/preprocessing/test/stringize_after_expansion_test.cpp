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

#include "breeze/preprocessing/stringize_after_expansion.hpp"
#include "breeze/testing/testing.hpp"
#include <cstring>

#define FOO 1
#define FOO2 FOO

#define BAR "a"
#define BAR2 BAR

#define FIRST_TOKEN multiple

int                 test_breeze_stringize_after_expansion() ;

namespace {

void
do_tests()
{
    BREEZE_CHECK( std::strcmp( BREEZE_STRINGIZE_AFTER_EXPANSION( FOO2 ),
                               "1" )  == 0 ) ;
    BREEZE_CHECK( std::strcmp( BREEZE_STRINGIZE_AFTER_EXPANSION( BAR2 ),
                               "\"a\"" )  == 0 ) ;

    BREEZE_CHECK( std::strcmp( BREEZE_STRINGIZE_AFTER_EXPANSION( FIRST_TOKEN
                                                                 tokens),
                               "multiple tokens" ) == 0 ) ;
}

}

int
test_breeze_stringize_after_expansion()
{
    return breeze::test_runner::instance().run(
             "BREEZE_STRINGIZE_AFTER_EXPANSION()",
             { do_tests } ) ;
}
