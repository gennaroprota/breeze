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

#include "breeze/time/c_clock_timer.hpp"
#include <ctime>
#include <stdexcept>

namespace breeze_ns {
namespace           {

breeze::c_clock_clock::duration
to_duration_type( std::clock_t tick )
{
    return breeze::c_clock_clock::duration(
            static_cast< long double >( tick )              /
            static_cast< long double >( CLOCKS_PER_SEC )    *
            breeze::c_clock_clock::period::den              /
            breeze::c_clock_clock::period::num
        ) ;
}

std::clock_t
retrieve()
{
    std::clock_t const  result = std::clock() ;
    return result != static_cast< std::clock_t >( -1 )
        ? result
        : throw std::runtime_error( "std::clock() failed (e.g. because the time"
                                    " elapsed is not available or because it is"
                                    " too long to be represented in a"
                                    " std::clock_t)" ) ;
}

[[ noreturn ]] void
throw_because_of_wrap_around()
{
    throw std::runtime_error( "std::clock() wrapped around" ) ;
}

}

c_clock_clock::time_point
c_clock_clock::now()
{
    return time_point( to_duration_type( retrieve() ) ) ;
}

c_clock_clock::duration
c_clock_clock::resolution()
{
    std::clock_t        start ;
    std::clock_t        end ;

    std::clock_t const  s = retrieve() ;
    while ( s     == ( start = retrieve() ) ) { }
    while ( start == (   end = retrieve() ) ) { }

    if ( end < start ) {
        throw_because_of_wrap_around() ;
    }

    return to_duration_type( end - start ) ;
}

}
