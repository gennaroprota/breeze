// ===========================================================================
//                     Copyright 2006-2021 Gennaro Prota
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

//      performance_counter_clock:
//      ==========================
//
//!     \brief
//!         A clock for our `timer` template using Windows'
//!         `QueryPerformanceCounter()`.
//!
//!     Most times, you'll just use `performance_counter_timer`, and not
//!     this class directly.
// ---------------------------------------------------------------------------
class performance_counter_clock
{
public:
    using               rep        = long long ;
    using               period     = std::nano ;
    using               duration   = std::chrono::duration< rep, period > ;
    using               time_point =
        std::chrono::time_point< performance_counter_clock > ;

    static constexpr bool
                        is_steady = true ;

    //!     \return
    //!         The current time.
    //!
    //!     \par Exceptions
    //!         A `last_api_error` if an error occurs.
    // -----------------------------------------------------------------------
    static time_point   now() ;

    //!     \return
    //!         The clock resolution.
    //!
    //!     \par Exceptions
    //!         A `last_api_error` if the resolution can't be obtained.
    //!
    //!     See the \link timer timer\endlink documentation.
    // -----------------------------------------------------------------------
    static duration     resolution() ;
} ;

typedef timer< performance_counter_clock >
                    performance_counter_timer ;

}

#endif
