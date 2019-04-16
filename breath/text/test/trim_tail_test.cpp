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

#include "breath/text/trim_tail.hpp"
#include "breath/text/set_of_chars.hpp"

#include <string>

// gps temp
#include "breath/diagnostics/assert.hpp"
#define DO_TEST( x ) BREATH_ASSERT( x )
////////////////

int
main()
{
    using breath::trim_tail ;

    DO_TEST( trim_tail( "" ) == "" ) ;
    DO_TEST( trim_tail( " " ) == "" ) ;
    DO_TEST( trim_tail( "\t" ) == "" ) ;
    DO_TEST( trim_tail( " \t" ) == "" ) ;
    DO_TEST( trim_tail( "\t " ) == "" ) ;


    DO_TEST( trim_tail( "abc  " ) == "abc" ) ;
    DO_TEST( trim_tail( "abc \t" ) == "abc" ) ;
    DO_TEST( trim_tail( "abc a" ) == "abc a" ) ;

    DO_TEST( trim_tail( "abcd", breath::set_of_chars( "db" ) ) == "abc" ) ;
    DO_TEST( trim_tail( "abcd", breath::set_of_chars( "badc" ) ) == "" ) ;
    DO_TEST( trim_tail( "a", breath::set_of_chars( "bcde" ) ) == "a" ) ;
    DO_TEST( trim_tail( "abcd", breath::set_of_chars( "bce" ) ) == "abcd" ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
