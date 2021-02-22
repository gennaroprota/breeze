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

#include "breeze/preprocessing/stringize.hpp"
#include "breeze/testing/testing.hpp"
#include <cstring>

#define FOO 1
#define FOO2 FOO

int                 test_breeze_stringize() ;

namespace {

void
do_tests()
{
    BREEZE_CHECK( std::strcmp( BREEZE_STRINGIZE( FOO2 ), "FOO2" )  == 0 ) ;
    BREEZE_CHECK( std::strcmp( BREEZE_STRINGIZE( "FOO2" ), "\"FOO2\"" ) == 0 ) ;

    BREEZE_CHECK( std::strcmp( BREEZE_STRINGIZE( multiple tokens ),
                                                "multiple tokens") == 0 ) ;

    //      Make a dummy use of the FOO2 macro, to avoid a
    //      -Wunused-macros warning from GCC.
    // -----------------------------------------------------------------------
    int const           dummy = FOO2 ;
    static_cast< void >( dummy ) ;
}

}

int
test_breeze_stringize()
{
    return breeze::test_runner::instance().run(
        "BREEZE_STRINGIZE()",
        { do_tests } ) ;
}
