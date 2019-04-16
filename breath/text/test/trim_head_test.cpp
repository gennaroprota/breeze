// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/text/set_of_chars.hpp"
#include "breath/text/trim_head.hpp"

// gps temp
#include "breath/diagnostics/assert.hpp"
#define DO_TEST( x ) BREATH_ASSERT( x )
////////////////

int
main()
{
    using breath::trim_head ;
    using breath::set_of_chars ;

    DO_TEST( trim_head( "" ) == "" ) ;
    DO_TEST( trim_head( " " ) == "" ) ;
    DO_TEST( trim_head( "\t" ) == "" ) ;
    DO_TEST( trim_head( " \t" ) == "" ) ;
    DO_TEST( trim_head( "\t " ) == "" ) ;


    DO_TEST( trim_head( "  abc" ) == "abc" ) ;
    DO_TEST( trim_head( "\t abc" ) == "abc" ) ;
    DO_TEST( trim_head( "abc a" ) == "abc a" ) ;

    DO_TEST( trim_head( "abcd", set_of_chars( "ab" ) ) == "cd" ) ;
    DO_TEST( trim_head( "abcde", set_of_chars( "badc" ) ) == "e" ) ;
    DO_TEST( trim_head( "a", set_of_chars( "bcde" ) ) == "a" ) ;
    DO_TEST( trim_head( "abcd", set_of_chars( "bce" ) ) == "abcd" ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
