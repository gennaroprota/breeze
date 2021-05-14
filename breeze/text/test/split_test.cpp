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

#include "breeze/text/split.hpp"
#include "breeze/testing/testing.hpp"

#include <locale>
#include <string>
#include <vector>

int                 test_split() ;

namespace {

void
do_test_split()
{
    using               breeze::split ;

    {
        std::string const   s ;
        std::string const   separators = { '\0' } ;
        std::vector< std::string > const
                            v = split( s, separators ) ;
        BREEZE_CHECK( v.size() == 1 ) ;
        BREEZE_CHECK( v[ 0 ].empty() ) ;
    }

    {
        std::string const   s ;
        std::string const   no_separators ;
        std::vector< std::string > const
                            v = split( s, no_separators ) ;
        BREEZE_CHECK( v.size() == 1 ) ;
        BREEZE_CHECK( v[ 0 ].empty() ) ;
    }

    {
        std::string const   s( "abc" ) ;
        std::string const   no_separators ;
        std::vector< std::string > const
                            v = split( s, no_separators ) ;

        BREEZE_CHECK( v.size() == 1 ) ;
        BREEZE_CHECK( v[ 0 ] == s ) ;
    }

    {
        std::string const   s( "abcde" ) ;
        std::string const   separators = { '\0' } ;
        std::vector< std::string > const
                            v = split( s, separators ) ;

        BREEZE_CHECK( v.size() == 1 ) ;
        BREEZE_CHECK( v[ 0 ] == "abcde" ) ;
    }

    {
        std::vector< std::string > const
                            v = split( "*", "*" ) ;
        BREEZE_CHECK( v.size() == 2 ) ;
        BREEZE_CHECK( v[ 0 ].empty() ) ;
        BREEZE_CHECK( v[ 1 ].empty() ) ;
    }

    {
        std::vector< std::string > const
                            v = split( "**", "*" ) ;
        BREEZE_CHECK( v.size() == 3 ) ;
        BREEZE_CHECK( v[ 0 ].empty() ) ;
        BREEZE_CHECK( v[ 1 ].empty() ) ;
        BREEZE_CHECK( v[ 2 ].empty() ) ;
    }

    {
        std::string         s( "string1" ) ;
        s.push_back( 'X' ) ;
        s += "string2" ;
        s.push_back( 'Y' ) ;
        s += "string3" ;
        std::vector< std::string > const
                            v = split( s, "XY" ) ;

        BREEZE_CHECK( v.size() == 3 ) ;
        BREEZE_CHECK( v[ 0 ] == "string1" ) ;
        BREEZE_CHECK( v[ 1 ] == "string2" ) ;
        BREEZE_CHECK( v[ 2 ] == "string3" ) ;
    }

    {
        std::string         s( "string1" ) ;
        s.push_back( 'A' ) ;
        s += "string2" ;
        s.push_back( 'B' ) ;
        s += "string3" ;
        s.push_back( 'C' ) ;
        std::vector< std::string > const
                            v = split( s, "ABC" ) ;

        BREEZE_CHECK( v.size() == 4 ) ;
        BREEZE_CHECK( v[ 0 ] == "string1" ) ;
        BREEZE_CHECK( v[ 1 ] == "string2" ) ;
        BREEZE_CHECK( v[ 2 ] == "string3" ) ;
        BREEZE_CHECK( v[ 3 ].empty() ) ;
    }

    {
        std::string         s( "string1" ) ;
        s.push_back( '\0' ) ;
        s.push_back( '\0' ) ;
        s += "string3" ;
        std::string const   separators = { '\0' } ;
        std::vector< std::string > const
                            v = split( s, separators ) ;
        BREEZE_CHECK( v.size() == 3 ) ;
        BREEZE_CHECK( v[ 0 ] == "string1" ) ;
        BREEZE_CHECK( v[ 1 ].empty() ) ;
        BREEZE_CHECK( v[ 2 ] == "string3" ) ;
    }

    {
        std::string const   only_separators( "x" ) ;
        std::string const   separators = only_separators ;
        std::vector< std::string > const
                            v = split( only_separators, separators ) ;
        BREEZE_CHECK( v.size() == 2 ) ;
        BREEZE_CHECK( v[ 0 ].empty() ) ;
        BREEZE_CHECK( v[ 1 ].empty() ) ;
    }
}

void
do_test_split_if()
{
    {
        std::string const   s( "aBc" ) ;
        auto const          is_upper =
            []( char c )
            {
                return std::isupper( c, std::locale::classic() ) ;
            } ;
        std::vector< std::string > const
                            v = breeze::split_if( s, is_upper ) ;
        BREEZE_CHECK( v.size() == 2 ) ;
        BREEZE_CHECK( v[ 0 ] == "a" ) ;
        BREEZE_CHECK( v[ 1 ] == "c" ) ;
    }
}

}

int
test_split()
{
    return breeze::test_runner::instance().run(
        "split() and split_if()",
        { do_test_split,
          do_test_split_if } ) ;
}
