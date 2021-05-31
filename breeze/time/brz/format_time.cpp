// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2008-2011 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/time/format_time.hpp"
#include "breeze/time/private/thread_safe_reentrant_time_functions.hpp"
#include <iomanip>
#include <ostream>
#include <time.h>

namespace breeze_ns {

//      The extended date and time could be obtained (since C99 and
//      C++11) with %F and %T, respectively. But I'm not sure how many
//      libraries have updated their implementation of strftime() to
//      support these specifiers.
// ---------------------------------------------------------------------------
extern char const   iso8601_basic_date[]    = "%Y%m%d" ;
extern char const   iso8601_extended_date[] = "%Y-%m-%d" ;

extern char const   iso8601_basic_time[]    = "%H%M%S" ;
extern char const   iso8601_extended_time[] = "%H:%M:%S" ;

void
format_time( std::string const & format,
             std::ostream & dest,
             time_kind kind,
             std::chrono::system_clock::time_point const & time_point )
{
    using namespace time_private ;

    std::time_t const   time_stamp =
        std::chrono::system_clock::to_time_t( time_point ) ;
    tm                  broken_down ;
    tm const * const    p = ( kind == time_kind::utc
            ? thread_safe_reentrant_gmtime(    &time_stamp, &broken_down )
            : thread_safe_reentrant_localtime( &time_stamp, &broken_down ) )
            ;
    if ( p != nullptr ) {
        dest << std::put_time( &broken_down, format.c_str() ) ;
    } else {
        dest.setstate( std::ios::failbit ) ;
    }
}

}
