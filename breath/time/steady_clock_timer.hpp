// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A timer based on \c std::chrono::steady_clock.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_nLtyKWctWF4nTnEMJ4Y66pLLeGE7RNze
#define BREATH_GUARD_nLtyKWctWF4nTnEMJ4Y66pLLeGE7RNze

#include "breath/top_level_namespace.hpp"
#include "breath/time/timer.hpp"
#include <chrono>

namespace breath_ns {

//      steady_clock_policy:
//      ====================
//
//!     \brief A policy for our \c timer template using \c
//!            std::chrono::steady_clock.
//!
//!     \note
//!         This policy does not provide the \c resolution() member.
// ---------------------------------------------------------------------------
class steady_clock_policy
{
public:
    //!     Deleted copy constructor.
    // -----------------------------------------------------------------------
                        steady_clock_policy( steady_clock_policy const & ) =
                                                                        delete ;

    //!     Deleted copy assignment operator.
    // -----------------------------------------------------------------------
    steady_clock_policy &
                        operator =(          steady_clock_policy const & ) =
                                                                        delete ;

    //!     A typedef for \c std::chrono::steady_clock::duration.
    // -----------------------------------------------------------------------
    typedef std::chrono::steady_clock::duration
                        duration_type ;

    //!     See the \link timer timer\endlink documentation.
    // -----------------------------------------------------------------------
                        steady_clock_policy() ;

    //!     See the \link timer timer\endlink documentation.
    // -----------------------------------------------------------------------
    void                start() noexcept ;

    //!     See the \link timer timer\endlink documentation.
    // -----------------------------------------------------------------------
    duration_type       elapsed() const noexcept ;

private:
    std::chrono::steady_clock::time_point
                        m_start_time ;
} ;

typedef timer< steady_clock_policy >
                        steady_clock_timer ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
