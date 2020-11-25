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

#include "breeze/path/extension.hpp"
#include "breeze/testing/testing.hpp"

int                 test_extension() ;

namespace {

void
do_test()
{
    using               breeze::extension ;

    BREEZE_CHECK( extension( "" )                == "" ) ;
    BREEZE_CHECK( extension( "." )               == "" ) ;
    BREEZE_CHECK( extension( ".." )              == "" ) ;

    BREEZE_CHECK( extension( ".dotfile" )        == "" ) ;
    BREEZE_CHECK( extension( ".dotfile.txt" )    == ".txt" ) ;
    BREEZE_CHECK( extension( ".dotfile.tar.gz" ) == ".gz" ) ;

    BREEZE_CHECK( extension( "my_file" )        == "" ) ;
    BREEZE_CHECK( extension( "my_file." )       == "." ) ;
    BREEZE_CHECK( extension( "my_file.txt.exe") == ".exe" ) ;

    BREEZE_CHECK( extension( "C:/a.b/" )      == "" ) ;
    BREEZE_CHECK( extension( "C:/a.b/file" )  == "" ) ;
    BREEZE_CHECK( extension( "C:/a.b/file." ) == "." ) ;
    BREEZE_CHECK( extension( "/my_file.exe" ) == ".exe" ) ;

    BREEZE_CHECK( extension( "/dir/." )       == "" ) ;
    BREEZE_CHECK( extension( "/dir/.." )      == "" ) ;

    BREEZE_CHECK( extension( "/dir/.dotfile" )        == "" ) ;
    BREEZE_CHECK( extension( "/dir/.dotfile.txt" )    == ".txt" ) ;
    BREEZE_CHECK( extension( "/dir/.dotfile.tar.gz" ) == ".gz" ) ;

    BREEZE_CHECK( extension(
        "C:/Documents and Settings/Genny/Desktop/my_file.bat" ) == ".bat" ) ;
}

}

int
test_extension()
{
    using namespace breeze ;

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
