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

#include "breath/testing/testing.hpp"
#include "breath/text/split.hpp"

#include <iostream>
#include <string>
#include <vector>

int                 test_split() ;

namespace {

void
do_test()
{
    using               breath::split ;

    {
        std::string const   s ;
        std::string const   separators = { '\0' } ;
        std::vector< std::string > const
                            v = split( s, separators) ;
        BREATH_CHECK( v.size() == 1 ) ;
        BREATH_CHECK( v[ 0 ].empty() ) ;
    }

    {
        std::string const   s ;
        std::string const   no_separators ;
        std::vector< std::string > const
                            v = split( s, no_separators ) ;
        BREATH_CHECK( v.size() == 1 ) ;
        BREATH_CHECK( v[ 0 ].empty() ) ;
    }

    {
        std::string const   s( "abc" ) ;
        std::string const   no_separators ;
        std::vector< std::string > const
                            v = split( s, no_separators ) ;

        BREATH_CHECK( v.size() == 1 ) ;
        BREATH_CHECK( v[ 0 ] == s ) ;
    }

    {
        std::string const   s( "abcde" ) ;
        std::string const   separators = { '\0' } ;
        std::vector< std::string > const
                            v = split( s, separators ) ;

        BREATH_CHECK( v.size() == 1 ) ;
        BREATH_CHECK( v[ 0 ] == "abcde" ) ;
    }

    {
        std::vector< std::string > const
                            v = split( "*", "*" ) ;
        BREATH_CHECK( v.size() == 2 ) ;
        BREATH_CHECK( v[ 0 ].empty() ) ;
        BREATH_CHECK( v[ 1 ].empty() ) ;
    }

    {
        std::vector< std::string > const
                            v = split( "**", "*" ) ;
        BREATH_CHECK( v.size() == 3 ) ;
        BREATH_CHECK( v[ 0 ].empty() ) ;
        BREATH_CHECK( v[ 1 ].empty() ) ;
        BREATH_CHECK( v[ 2 ].empty() ) ;
    }

    {
        std::string         s( "string1" ) ;
        s.push_back( 'X' ) ;
        s += "string2" ;
        s.push_back( 'Y' ) ;
        s += "string3" ;
        std::vector< std::string > const
                            v = split( s, "XY" ) ;

        BREATH_CHECK( v.size() == 3 ) ;
        BREATH_CHECK( v[ 0 ] == "string1" ) ;
        BREATH_CHECK( v[ 1 ] == "string2" ) ;
        BREATH_CHECK( v[ 2 ] == "string3" ) ;
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

        BREATH_CHECK( v.size() == 4 ) ;
        BREATH_CHECK( v[ 0 ] == "string1" ) ;
        BREATH_CHECK( v[ 1 ] == "string2" ) ;
        BREATH_CHECK( v[ 2 ] == "string3" ) ;
        BREATH_CHECK( v[ 3 ].empty() ) ;
    }

    {
        std::string         s( "string1" ) ;
        s.push_back( '\0' ) ;
        s.push_back( '\0' ) ;
        s += "string3" ;
        std::string const   separators = { '\0' } ;
        std::vector< std::string > const
                            v = split( s, separators ) ;
        BREATH_CHECK( v.size() == 3 ) ;
        BREATH_CHECK( v[ 0 ] == "string1" ) ;
        BREATH_CHECK( v[ 1 ].empty() ) ;
        BREATH_CHECK( v[ 2 ] == "string3" ) ;
    }

    {
        std::string const   only_separators( "x" ) ;
        std::string const   separators = only_separators ;
        std::vector< std::string > const
                            v = split( only_separators, separators ) ;
        BREATH_CHECK( v.size() == 2 ) ;
        BREATH_CHECK( v[ 0 ].empty() ) ;
        BREATH_CHECK( v[ 1 ].empty() ) ;
    }
}

}

int
test_split()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run(
             "split()",
             { do_test } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
