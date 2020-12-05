// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/path/base_file_name.hpp"
#include "breeze/preprocessing/stringize_after_expansion.hpp"
#include "breeze/testing/testing.hpp"
#include <cstring>

int                 test_base_file_name() ;

namespace {

bool
is_windows()
{
    return std::strcmp( BREEZE_STRINGIZE_AFTER_EXPANSION( BREEZE_SYSTEM ),
                        "windows" ) == 0 ;
}

void
do_test()
{
    using               breeze::base_file_name ;

    BREEZE_CHECK( base_file_name( "" )      == "" ) ;
    BREEZE_CHECK( base_file_name( "my_file" )      == "my_file" ) ;
    BREEZE_CHECK( base_file_name( "/my_file" )     == "my_file" ) ;

    BREEZE_CHECK( base_file_name( "/usr/")           == "" ) ;
    BREEZE_CHECK( base_file_name( "/usr/lib/my_lib") == "my_lib" ) ;

    if ( is_windows() ) {
        BREEZE_CHECK( base_file_name(
            "C:\\Documents and Settings\\Genny\\Desktop\\my_file" )
            == "my_file" ) ;
    }
}

}

int
test_base_file_name()
{
    return breeze::test_runner::instance().run(
        "base_file_name()",
        { do_test } ) ;
}
