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

#include "breath/text/begins_with.hpp"

#include <string>

// gps temp
#include "breath/diagnostics/assert.hpp"
#define DO_TEST( x ) BREATH_ASSERT( x )
////////////////

int
main()
{
    using breath::begins_with ;

    std::string const   empty ;
    DO_TEST( begins_with( empty, empty ) ) ;

    DO_TEST(   begins_with( "",  ""  ) ) ;
    DO_TEST(   begins_with( "a", ""  ) ) ;
    DO_TEST(   begins_with( "a", "a" ) ) ;
    DO_TEST( ! begins_with( "",  "a" ) ) ;
    DO_TEST( ! begins_with( "a", "ab" ) ) ;

    // some space tests
    DO_TEST(   begins_with( " a",  " "   ) ) ;
    DO_TEST(   begins_with( " a  ", " "   ) ) ;
    DO_TEST(   begins_with( "  a", "  "  ) ) ;
    DO_TEST( ! begins_with( " a",  "  "  ) ) ;
    DO_TEST( ! begins_with( " a",  "a"   ) ) ;
    DO_TEST( ! begins_with( "          ", "\t" ) ) ;

    DO_TEST(   begins_with( "abc", "ab"   ) ) ;
    DO_TEST( ! begins_with( "ab", "abc"   ) ) ;
    DO_TEST( ! begins_with( "bcd", "abcd" ) ) ;

    // check that embedded NULs are handled correctly
    std::string         s ;
    s.push_back( 'a' ) ;
    s.push_back( '\0' ) ;
    s.push_back( 'b' ) ;

    std::string         t ;
    t.push_back( '\0' ) ;
    DO_TEST( ! begins_with( s, t) ) ;
    t = "a" ;
    t.push_back( '\0' ) ;
    DO_TEST( begins_with( s, t ) ) ;
    DO_TEST( begins_with( s, s ) ) ;
    DO_TEST( begins_with( t, t ) ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
