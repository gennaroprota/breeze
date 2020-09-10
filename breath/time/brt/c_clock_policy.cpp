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

#include "breath/time/c_clock_policy.hpp"
#include "breath/diagnostics/assert.hpp"
#include <stdexcept>

namespace breath_ns {
namespace           {

auto const          invalid_tick = static_cast< std::clock_t >( -1 ) ;

breath::c_clock_policy::duration_type
to_duration_type( std::clock_t elapsed )
{
    return breath::c_clock_policy::duration_type(
            static_cast< long double >( elapsed )                  /
            static_cast< long double >( CLOCKS_PER_SEC )           *
                breath::c_clock_policy::duration_type::period::den /
                breath::c_clock_policy::duration_type::period::num
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

c_clock_policy::c_clock_policy()
    :   m_start_tick( invalid_tick )
{
}

void
c_clock_policy::start()
{
    //      Synchronize our start.
    // -----------------------------------------------------------------------
    std::clock_t const  s = retrieve() ;
    while ( s == ( m_start_tick = retrieve() ) ) { }
}

c_clock_policy::duration_type
c_clock_policy::elapsed() const
{
    BREATH_ASSERT( m_start_tick != invalid_tick ) ;

    std::clock_t const  now = retrieve() ;

    if ( now < m_start_tick ) {
        throw_because_of_wrap_around() ;
    }

    return to_duration_type( now - m_start_tick ) ;
}

c_clock_policy::duration_type
c_clock_policy::resolution() const
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

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
