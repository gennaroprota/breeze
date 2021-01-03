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

#include "breeze/conversion/roman.hpp"
#include "breeze/environment/get_environment_variable.hpp"
#include "breeze/testing/testing.hpp"

#include <algorithm>
#include <fstream>
#include <ios>
#include <iterator>
#include <locale>
#include <sstream>
#include <string>

int                 test_roman() ;

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
    std::string const   breeze_root = breeze::get_environment_variable(
                                                    "BREEZE_ROOT" ).value() ;
    std::ifstream       is( breeze_root
                            + "/breeze/conversion/test/a006968.txt" ) ;

    BREEZE_CHECK( is.good() ) ;

    //      Skip the first lines.
    // -----------------------------------------------------------------------
    int const           lines_to_skip = 14 ;
    for ( int i = 0 ; i < lines_to_skip ; ++ i ) {
        std::string         line ;
        std::getline( is, line ) ;
    }

    int const           max_roman = 3999 ;
    int                 n ;
    do  {
        is >> n ;
        char                equal_sign ;
        is >> equal_sign ;
        std::string         upper_expected ;
        is >> upper_expected ;

        BREEZE_CHECK( is.good() ) ;

        std::ostringstream  strm ;
        breeze::roman const roman( n ) ;

        strm << std::uppercase << roman ;
        std::string const   upper_actual = strm.str() ;

        strm.str( "" ) ;
        strm << std::nouppercase << roman ;
        std::string const   lower_actual = strm.str() ;

        BREEZE_CHECK( upper_actual == upper_expected ) ;
        BREEZE_CHECK( lower_actual == classic_to_lower( upper_expected ) ) ;
    } while ( n != max_roman ) ;
}

void
out_of_range_integer_triggers_assert()
{
    BREEZE_CHECK_THROW( breeze::assert_failure, breeze::roman(    0 ) ) ;
    BREEZE_CHECK_THROW( breeze::assert_failure, breeze::roman( 4000 ) ) ;
}

}

int
test_roman()
{
    return breeze::test_runner::instance().run(
        "roman",
        { check,
          out_of_range_integer_triggers_assert } ) ;
}
