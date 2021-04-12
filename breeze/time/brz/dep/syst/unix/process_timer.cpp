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

#include "breeze/diagnostics/last_api_error.hpp"
#include <sys/times.h>
#include <unistd.h>
#include <chrono>

namespace breeze_ns {
namespace           {

long
get_ticks_per_second()
{
    long const          t = sysconf( _SC_CLK_TCK ) ;

    if ( t == -1 ) {
        throw last_api_error( "sysconf( _SC_CLK_TCK ) failed" ) ;
    }

    return t ;
}

process_timer::duration
ticks_to_duration( clock_t ticks )
{
    static long const   ticks_per_second = get_ticks_per_second() ;
    double const        second_count =
        static_cast< double >( ticks ) /
        static_cast< double >( ticks_per_second ) ;

    return std::chrono::duration_cast< process_timer::duration >(
            std::chrono::duration< double >( second_count ) ) ;
}

process_duration
get_process_times()
{
    using               steady_clock = std::chrono::steady_clock ;

    tms                 t ;
    clock_t const       ret = times( &t ) ;
    steady_clock::time_point const
                        now = steady_clock::now() ;

    if ( ret == std::clock_t( -1 ) ) {
        throw last_api_error( "times() failed" ) ;
    }

    process_duration    result ;
    result.system = ticks_to_duration( t.tms_stime + t.tms_cstime ) ;
    result.user   = ticks_to_duration( t.tms_utime + t.tms_cutime ) ;
    result.wall   = now - steady_clock::time_point (
                            steady_clock::duration( 0 ) ) ;

    return result ;
}

}
}
