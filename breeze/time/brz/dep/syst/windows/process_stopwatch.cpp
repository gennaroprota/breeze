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
#include <Windows.h>
#include <chrono>
#include <cstdint>

namespace breeze_ns {
namespace           {

std::int64_t
to_int64( FILETIME const & ft )
{
    int const           dword_bits = 32 ;
    return ( static_cast< std::int64_t >( ft.dwHighDateTime ) << dword_bits ) |
           ft.dwLowDateTime ;
}

process_stopwatch::duration
filetime_to_duration( FILETIME const & ft )
{
    long const          ticks_per_second = 10'000'000 ;
    double const        second_count =
        static_cast< double >( to_int64( ft ) ) /
        static_cast< double >( ticks_per_second ) ;

    return std::chrono::duration_cast< process_stopwatch::duration >(
            std::chrono::duration< double >( second_count ) ) ;
}

process_duration
get_process_times()
{
    using               steady_clock = std::chrono::steady_clock ;

    process_duration    result ;

    FILETIME            creation_time ;
    FILETIME            exit_time ;
    FILETIME            kernel_time ;
    FILETIME            user_time ;

    int const           ret =
        GetProcessTimes( GetCurrentProcess(), &creation_time, &exit_time,
                            &kernel_time, &user_time ) ;
    steady_clock::time_point const
                        now = steady_clock::now() ;

    if ( ret == 0 ) {
        throw last_api_error( "GetProcessTimes() failed" ) ;
    }

    result.user   = filetime_to_duration( user_time   ) ;
    result.system = filetime_to_duration( kernel_time ) ;
    result.wall   = now - steady_clock::time_point(
                            steady_clock::duration( 0 ) ) ;

    return result ;
}

}

}
