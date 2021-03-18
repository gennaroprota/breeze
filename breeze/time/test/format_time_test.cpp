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

//      This is not guaranteed, but it's true on all the systems we care
//      about, for now.
// ---------------------------------------------------------------------------
void
format_time_of_zero_returns_unix_epoch()
{
    breeze::maybe< std::string >
                        m = format_time( breeze::iso8601_basic_date,
                            time_kind::utc, 0 ) ;
    BREEZE_CHECK( m.is_valid() && m.value() == "19700101" ) ;
}

}

int
test_format_time()
{
    return breeze::test_runner::instance().run(
        "format_time()",
        { format_time_of_minus_one_returns_invalid_regardless_of_format_and_kind,
          format_time_of_zero_returns_unix_epoch } ) ;
}
