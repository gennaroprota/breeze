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

#include "breath/path/base_file_name.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>

int                 test_base_file_name() ;

namespace {

void
do_test()
{
    using               breath::base_file_name ;

    BREATH_CHECK( base_file_name( "" )      == "" ) ;
    BREATH_CHECK( base_file_name( "my_file" )      == "my_file" ) ;
    BREATH_CHECK( base_file_name( "/my_file" )     == "my_file" ) ;

    BREATH_CHECK( base_file_name( "/usr/")           == "" ) ;
    BREATH_CHECK( base_file_name( "/usr/lib/my_lib") == "my_lib" ) ;
    BREATH_CHECK( base_file_name(
        "C:\\Documents and Settings\\Genny\\Desktop\\my_file" ) == "my_file" ) ;
}

}

int
test_base_file_name()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run(
             "base_file_name()",
             { do_test } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
