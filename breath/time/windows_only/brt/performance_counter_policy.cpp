// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/time/windows_only/performance_counter_policy.hpp"
#include "breath/diagnostics/last_api_error.hpp"
#include <Windows.h>

namespace breath_ns {

performance_counter_policy::performance_counter_policy()
{
    //      Note that start() is not called here. It will be called by
    //      the timer template, if needed. Note that this causes the
    //      member m_start to be left uninitialized.
    // -----------------------------------------------------------------------
    LARGE_INTEGER       f ;
    if ( QueryPerformanceFrequency( &f ) == 0 ) {
        throw last_api_error( "QueryPerformanceFrequency() failed" ) ;
    }
    m_frequency = static_cast< duration_type >( f.QuadPart ) ;
}

void
performance_counter_policy::start()
{
    LARGE_INTEGER       li ;
    if ( QueryPerformanceCounter( &li ) == 0 ) {
        throw last_api_error( "QueryPerformanceCounter() failed" ) ;
    }
    m_start = static_cast< duration_type >( li.QuadPart ) ;

}

performance_counter_policy::duration_type
performance_counter_policy::elapsed() const
{
    LARGE_INTEGER       li ;
    if ( QueryPerformanceCounter( &li ) == 0 ) {
        throw last_api_error( "QueryPerformanceCounter() failed" ) ;
    }
    return ( li.QuadPart - m_start ) * resolution() ;
}

performance_counter_policy::duration_type
performance_counter_policy::resolution() const
{
    // resolution is in milliseconds
    return 1000.0L / m_frequency ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
