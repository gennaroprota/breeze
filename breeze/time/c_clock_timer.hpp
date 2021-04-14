// ===========================================================================
//                     Copyright 2006-2021 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A timer using `std::clock()`.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_s9RhTgkTQviSRQ89lVvZRW16hRqlr1OA
#define BREEZE_GUARD_s9RhTgkTQviSRQ89lVvZRW16hRqlr1OA

#include "breeze/top_level_namespace.hpp"
#include "breeze/time/timer.hpp"
#include <chrono>

namespace breeze_ns {

//      c_clock_clock:
//      ==============
//
//!\brief
//!     A clock for our `timer` template using the C function `clock()`.
//!
//!     Most times, you'll just use `c_clock_timer`, and not this class
//!     directly.
//!
//!     \warning
//!         Note that on some (non-conforming) implementations `clock()`
//!         will actually measure wall-clock time. One such
//!         implementation is the Microsoft one:<br />
//!         <br />&nbsp;&nbsp;
//!    <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/clock>.
// ---------------------------------------------------------------------------
class c_clock_clock
{
public:
    using               rep        = double ;
    using               period     = std::milli ;
    using               duration   = std::chrono::duration< rep, period > ;
    using               time_point = std::chrono::time_point< c_clock_clock > ;

    static constexpr bool
                        is_steady = true ;

    //!     \return
    //!         The current time.
    //!
    //!     \par Exceptions
    //!         A `std::runtime_error` if `std::clock()` fails.
    // -----------------------------------------------------------------------
    static time_point   now() ;

    //!     \return
    //!         An estimate of the clock resolution. May return slightly
    //!         different values from call to call.
    //!
    //!     \par Exceptions
    //!         A `std::runtime_error` if it detects wrap-around (it
    //!         only detects \e some wrap-arounds), or if `std::clock()`
    //!         fails.
    // -----------------------------------------------------------------------
    static duration     resolution() ;
} ;

typedef timer< c_clock_clock >
                    c_clock_timer ;

}

#endif
