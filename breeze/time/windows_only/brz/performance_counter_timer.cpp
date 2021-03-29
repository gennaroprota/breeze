// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2006-2021 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/time/windows_only/performance_counter_timer.hpp"
#include "breeze/diagnostics/last_api_error.hpp"
#include <Windows.h>

namespace breeze_ns {
namespace           {

long long
get_count()
{
    LARGE_INTEGER       count ;
    if ( QueryPerformanceCounter( &count ) == 0 ) {
        throw last_api_error( "QueryPerformanceCounter() failed" ) ;
    }

    return count.QuadPart ;
}

typedef breeze::performance_counter_clock::duration
                    duration ;

typedef breeze::performance_counter_clock::time_point
                    time_point ;

duration
get_resolution()
{
    LARGE_INTEGER       f ;
    if ( QueryPerformanceFrequency( &f ) == 0 ) {
        throw last_api_error( "QueryPerformanceFrequency() failed" ) ;
    }

    return duration(
        duration::period::den /
        f.QuadPart /
        duration::period::num
    ) ;
}

}

time_point
performance_counter_clock::now()
{
    return time_point( get_count() * resolution() ) ;
}

performance_counter_clock::duration
performance_counter_clock::resolution()
{
    static duration const
                        res = get_resolution() ;
    return res ;
}

}
