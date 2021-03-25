// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A timer using Windows' `QueryPerformanceCounter()`.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_xQJo3uSTt7ypxnH7y1CyRR3fJM5i3dsb
#define BREEZE_GUARD_xQJo3uSTt7ypxnH7y1CyRR3fJM5i3dsb

#include "breeze/top_level_namespace.hpp"
#include "breeze/time/timer.hpp"
#include <chrono>

namespace breeze_ns {

//      performance_counter_policy:
//      ===========================
//
//!     \brief
//!         A policy for our `timer` template using Windows'
//!         `QueryPerformanceCounter()`.
// ---------------------------------------------------------------------------
class performance_counter_policy
{
public:
    //!     Deleted copy constructor.
    // -----------------------------------------------------------------------
    performance_counter_policy( performance_counter_policy const & ) = delete ;

    //!     Deleted copy assignment operator.
    // -----------------------------------------------------------------------
    performance_counter_policy &
                    operator =( performance_counter_policy const & ) = delete ;

    //!     The type used to represent elapsed times.
    // -----------------------------------------------------------------------
    typedef std::chrono::duration< long long, std::nano >
                        duration_type ;

    //!     Leaves this object in an undefined state. The only action
    //!     that can be performed on a just constructed policy object is
    //!     to call start().
    //!
    //!     See the \link timer timer\endlink documentation.
    // -----------------------------------------------------------------------
                        performance_counter_policy() ;

    //!     Starts or restarts measurement (see elapsed()).
    //!
    //!     \par Exceptions
    //!         A `last_api_error` if an error occurs.
    //!
    //!     See the \link timer timer\endlink documentation.
    // -----------------------------------------------------------------------
    void                start() ;

    //!     \return
    //!         The time elapsed from the last (re)start.
    //!
    //!     \pre
    //!         The function start() has been called at least once.
    //!
    //!     \par Exceptions
    //!         A `last_api_error` if an error occurs.
    //!
    //!     See the \link timer timer\endlink documentation.
    // -----------------------------------------------------------------------
    duration_type       elapsed() const ;

    //!     \return
    //!         The timer resolution.
    //!
    //!     \par Exceptions
    //!         A `last_api_error` if the resolution can't be obtained.
    //!
    //!     See the \link timer timer\endlink documentation.
    // -----------------------------------------------------------------------
    duration_type       resolution() const ;

private:
    long long           m_start ;
} ;

typedef timer< performance_counter_policy >
                    performance_counter_timer ;

}

#endif
