// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2006-2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/path/extension.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>

int                 test_extension() ;

namespace {

void
do_test()
{
    using               breath::extension ;

    BREATH_CHECK( extension( "" )                == "" ) ;
    BREATH_CHECK( extension( "." )               == "" ) ;
    BREATH_CHECK( extension( ".." )              == "" ) ;

    BREATH_CHECK( extension( ".dotfile" )        == "" ) ;
    BREATH_CHECK( extension( ".dotfile.txt" )    == ".txt" ) ;
    BREATH_CHECK( extension( ".dotfile.tar.gz" ) == ".gz" ) ;

    BREATH_CHECK( extension( "my_file" )        == "" ) ;
    BREATH_CHECK( extension( "my_file." )       == "." ) ;
    BREATH_CHECK( extension( "my_file.txt.exe") == ".exe" ) ;

    BREATH_CHECK( extension( "C:/a.b/" )      == "" ) ;
    BREATH_CHECK( extension( "C:/a.b/file" )  == "" ) ;
    BREATH_CHECK( extension( "C:/a.b/file." ) == "." ) ;
    BREATH_CHECK( extension( "/my_file.exe" ) == ".exe" ) ;

    BREATH_CHECK( extension( "/dir/." )       == "" ) ;
    BREATH_CHECK( extension( "/dir/.." )      == "" ) ;

    BREATH_CHECK( extension( "/dir/.dotfile" )        == "" ) ;
    BREATH_CHECK( extension( "/dir/.dotfile.txt" )    == ".txt" ) ;
    BREATH_CHECK( extension( "/dir/.dotfile.tar.gz" ) == ".gz" ) ;

    BREATH_CHECK( extension(
        "C:/Documents and Settings/Genny/Desktop/my_file.bat" ) == ".bat" ) ;
}

}

int
test_extension()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run(
             "extension()",
             { do_test } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
