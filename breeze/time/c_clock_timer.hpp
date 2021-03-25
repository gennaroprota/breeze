// ===========================================================================
//                        Copyright 2006 Gennaro Prota
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
#include <ctime>

namespace breeze_ns {

//      c_clock_policy:
//      ===============
//
//!     \brief
//!         A policy for our `timer` template using the C function
//!         `clock()`.
//!
//!     \warning
//!         Note that on some (non-conforming) implementations `clock()`
//!         will actually measure wall-clock time. One such
//!         implementation is the Microsoft one:<br />
//!         <br />&nbsp;&nbsp;
//!    <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/clock>.
// ---------------------------------------------------------------------------
class c_clock_policy
{
public:
    //!     Deleted copy constructor.
    // -----------------------------------------------------------------------
                        c_clock_policy( c_clock_policy const & ) = delete ;

    //!     Deleted copy assignment operator.
    // -----------------------------------------------------------------------
    c_clock_policy &    operator =(     c_clock_policy const & ) = delete ;

    //!     The type used to represent elapsed times.
    // -----------------------------------------------------------------------
    typedef std::chrono::duration< double, std::milli >
                        duration_type ;

    //!     Leaves this object in an undefined state. The only action
    //!     that can be performed on a just constructed policy object is
    //!     to call start().
    //!
    //!     See the \link timer timer\endlink documentation.
    // -----------------------------------------------------------------------
                        c_clock_policy() ;

    //!     Starts or restarts measurement (see elapsed()).
    //!
    //!     \par Exceptions
    //!         A `std::runtime_error` if `std::clock()` fails.
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
    //!         A `std::runtime_error` if it detects wrap-around (it
    //!         only detects \e some wrap-arounds), or if `std::clock()`
    //!         fails.
    //!
    //!     See the \link timer timer\endlink documentation.
    // -----------------------------------------------------------------------
    duration_type       elapsed() const ;

    //!     \return
    //!         An estimate of the timer resolution. May return slightly
    //!         different values from call to call.
    //!
    //!     \par Exceptions
    //!         A `std::runtime_error` if it detects wrap-around (it
    //!         only detects \e some wrap-arounds), or if `std::clock()`
    //!         fails.
    // -----------------------------------------------------------------------
    duration_type       resolution() const ;

private:
    std::clock_t        m_start_tick ;
} ;

typedef timer< c_clock_policy >
                    c_clock_timer ;

}

#endif
