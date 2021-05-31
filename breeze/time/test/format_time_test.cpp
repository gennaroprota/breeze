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
#include <chrono>
#include <ctime>
#include <sstream>

int                 test_format_time() ;

using breeze::format_time ;
using breeze::time_kind ;

namespace {

void
format_time_of_a_specific_date_time_returns_that_date_time()
{
    using std::chrono::system_clock ;

    std::tm             dt ;
    dt.tm_mday = 7 ;
    dt.tm_mon  = 3 ;
    dt.tm_year = 2021 - 1900 ;
    dt.tm_hour = 14 ;
    dt.tm_min  = 15 ;
    dt.tm_sec  = 23 ;

    dt.tm_isdst = -1 ;

    time_t const        time = std::mktime( &dt ) ;
    system_clock::time_point const
                        time_point = system_clock::from_time_t( time ) ;

    std::ostringstream  oss ;
    breeze::format_time( "%B %d, %Y %I:%M:%S %p",
                         oss,
                         time_kind::local,
                         time_point ) ;

    BREEZE_CHECK( ! oss.fail() ) ;
    BREEZE_CHECK( oss.str() == "April 07, 2021 02:15:23 PM" ) ;
}

}

int
test_format_time()
{
    return breeze::test_runner::instance().run(
        "format_time()",
        { format_time_of_a_specific_date_time_returns_that_date_time } ) ;
}
