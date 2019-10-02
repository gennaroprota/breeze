// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/conversion/roman.hpp"
#include "breath/environment/find_environment_string.hpp"
#include "breath/testing/testing.hpp"

#include <algorithm>
#include <fstream>
#include <ios>
#include <iterator>
#include <locale>
#include <string>
#include <sstream>
#include <iostream>

namespace {

std::string
classic_to_lower( std::string const & s )
{
    std::locale const   loc = std::locale::classic() ;

    std::string         result ;
    std::transform( s.cbegin(), s.cend(),
                    std::back_inserter( result ),
                    [ &loc ]( char c )
                    {
                        return std::tolower( c, loc ) ;
                    } ) ;

    return result ;
}

void
check()
{
    std::string const   breath_root = breath::find_environment_string(
                                                    "BREATH_ROOT" ).value() ;
    std::ifstream       is( breath_root
                            + "/breath/conversion/test/a006968.txt" ) ;

    // skip the first lines
    int const           lines_to_skip = 14 ;
    for ( int i = 0 ; i < lines_to_skip ; ++ i ) {
        std::string         s ;
        std::getline( is, s ) ;
    }

    int const           max_roman = 3999 ;
    int                 n ;
    do  {
        is >> n ;
        char                equal_sign ;
        is >> equal_sign ;
        std::string         upper_expected ;
        is >> upper_expected ;

        std::ostringstream  strm ;
        breath::roman const roman( n ) ;

        strm << std::uppercase << roman ;
        std::string const   upper_actual = strm.str() ;

        strm.str( "" ) ;
        strm << std::nouppercase << roman ;
        std::string const   lower_actual = strm.str() ;

        BREATH_CHECK( upper_actual == upper_expected ) ;
        BREATH_CHECK( lower_actual == ::classic_to_lower( upper_expected ) ) ;
    } while ( n != max_roman ) ;
}

}

int
main()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { check } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
