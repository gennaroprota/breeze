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

///////// gps
#include "breath/diagnostics/assert.hpp"
#define DO_TEST( x ) BREATH_ASSERT( x )
//////

int
main()
{
    using               breath::base_file_name ;

    DO_TEST( base_file_name( "" )      == "" ) ;
    DO_TEST( base_file_name( "my_file" )      == "my_file" ) ;
    DO_TEST( base_file_name( "/my_file" )     == "my_file" ) ;

    DO_TEST( base_file_name( "/usr/")           == "" ) ;
    DO_TEST( base_file_name( "/usr/lib/my_lib") == "my_lib" ) ;
    DO_TEST( base_file_name( "C:\\Documents and Settings\\Genny\\Desktop\\my_file" )
                                                            == "my_file" ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
