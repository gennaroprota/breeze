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

///////// gps
#include "breath/diagnostics/assert.hpp"
#define DO_TEST( x ) BREATH_ASSERT( x )
//////

int
main()
{
    using               breath::extension ;

    DO_TEST( extension( "" )                == "" ) ;
    DO_TEST( extension( "." )               == "" ) ;
    DO_TEST( extension( ".." )              == "" ) ;

    DO_TEST( extension( ".dotfile" )        == "" ) ;
    DO_TEST( extension( ".dotfile.txt" )    == ".txt" ) ;
    DO_TEST( extension( ".dotfile.tar.gz" ) == ".gz" ) ;

    DO_TEST( extension( "my_file" )        == "" ) ;
    DO_TEST( extension( "my_file." )       == "." ) ;
    DO_TEST( extension( "my_file.txt.exe") == ".exe" ) ;

    DO_TEST( extension( "C:/a.b/" )      == "" ) ;
    DO_TEST( extension( "C:/a.b/file" )  == "" ) ;
    DO_TEST( extension( "C:/a.b/file." ) == "." ) ;
    DO_TEST( extension( "/my_file.exe" ) == ".exe" ) ;

    DO_TEST( extension( "/dir/." )       == "" ) ;
    DO_TEST( extension( "/dir/.." )      == "" ) ;

    DO_TEST( extension( "/dir/.dotfile" )        == "" ) ;
    DO_TEST( extension( "/dir/.dotfile.txt" )    == ".txt" ) ;
    DO_TEST( extension( "/dir/.dotfile.tar.gz" ) == ".gz" ) ;

    DO_TEST( extension( "C:/Documents and Settings/Genny/Desktop/my_file.bat" )
                                                            == ".bat" ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
