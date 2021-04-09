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

process_timer::duration
filetime_to_duration( FILETIME const & ft )
{
    long const          ticks_per_second = 10'000'000 ;

    return std::chrono::duration_cast< process_timer::duration >(
            std::chrono::seconds( to_int64( ft ) / ticks_per_second ) ) ;
}

process_duration
get_process_times()
{
    process_duration    result ;

    FILETIME            creation_time ;
    FILETIME            exit_time ;
    FILETIME            kernel_time ;
    FILETIME            user_time ;

    if ( GetProcessTimes( GetCurrentProcess(), &creation_time, &exit_time,
                            &kernel_time, &user_time )  == 0 ) {
        throw last_api_error( "GetProcessTimes() failed" ) ;
    }

    result.user   = filetime_to_duration( user_time   ) ;
    result.system = filetime_to_duration( kernel_time ) ;

    return result ;
}

}

}
