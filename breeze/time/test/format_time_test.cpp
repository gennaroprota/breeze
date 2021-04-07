// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2021 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/time/format_time.hpp"
#include "breeze/testing/testing.hpp"
#include <ctime>

int                 test_format_time() ;

using breeze::format_time ;
using breeze::time_kind ;

namespace {

void
format_time_of_minus_one_returns_invalid_regardless_of_format_and_kind()
{
    std::time_t const   t = static_cast< std::time_t >( -1 ) ;

    for ( std::string const & format :
            { "", "%H", breeze::iso8601_basic_date, "some string" } ) {

        breeze::maybe< std::string >
                            m = format_time( format, time_kind::local, t ) ;
        BREEZE_CHECK( ! m.is_valid() ) ;

        m = format_time( format, time_kind::utc, t ) ;
        BREEZE_CHECK( ! m.is_valid() ) ;
    }
}

void
format_time_of_a_specific_date_time_returns_that_date_time()
{
    std::tm             dt ;
    dt.tm_mday = 7 ;
    dt.tm_mon  = 3 ;
    dt.tm_year = 2021 - 1900 ;
    dt.tm_hour = 14 ;
    dt.tm_min  = 15 ;
    dt.tm_sec  = 23 ;

    dt.tm_isdst = -1 ;

    time_t const        time = std::mktime( &dt ) ;
    breeze::maybe< std::string > const
                        m = format_time( "%B %d, %Y %I:%M:%S %p",
                            breeze::time_kind::local, time ) ;

    BREEZE_CHECK( m.is_valid() ) ;
    BREEZE_CHECK( m.value() == "April 07, 2021 02:15:23 PM" ) ;
}

}

int
test_format_time()
{
    return breeze::test_runner::instance().run(
        "format_time()",
        { format_time_of_minus_one_returns_invalid_regardless_of_format_and_kind,
          format_time_of_a_specific_date_time_returns_that_date_time } ) ;
}
