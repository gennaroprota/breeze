// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A policy-based timer class (class template).
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_Jr0D8xlNtWxnToeomoet20V4lz0qIYDd
#define BREEZE_GUARD_Jr0D8xlNtWxnToeomoet20V4lz0qIYDd

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//      timer:
//      ======
//
//!     \copybrief timer.hpp
//!
//!     A policy-based timer which allows the user to retrieve the
//!     amount of time elapsed from its start (i.e. a "stopwatch").
//!
//!     `Device` is a policy modeling the "clock device" concept: this
//!     can be a hardware device, a network time provider, a GPS clock
//!     or pretty much anything else. It must be <tt>
//!     DefaultConstructible</tt> and provide the member functions:
//!
//!      - `%start()`,
//!            which must start or restart the `Device`
//!
//!      - `%elapsed()`,
//!            which must return the amount of time elapsed from the
//!            last call to `%start()`
//!
//!     and the typedef:
//!
//!      - `duration_type`,
//!            which is the return type of `%elapsed()` and
//!            `%resolution()`; it must be a `std::chrono::duration`
//!
//!     Optionally, it may provide the member function:
//!
//!      - `%resolution()`,
//!            which must return the resolution of the `Device` or an
//!            estimate of it; note that the resolution is the smallest
//!            amount of time that the `Device` can measure and doesn't,
//!            in itself, tell anything about the \e accuracy
//!
//!     This function is only used in `timer::resolution()`, so if you
//!     don't need the latter, you can omit it.
// ---------------------------------------------------------------------------
template< class Device >
class timer
{
public:
    //!     Deleted copy constructor.
    //!
    //!     \par Rationale
    //!
    //!     Specifying copy semantics for a timer is a bit difficult
    //!     and, although it can probably be done, it's not worth it, as
    //!     who would copy a timer or a timer policy, anyway? (A timer
    //!     will, in practice, always be used like a Python context.)
    // -----------------------------------------------------------------------
                        timer(      timer const & ) = delete ;

    //!     Deleted copy assignment operator.
    //!
    //!     See the documentation of the (deleted) copy constructor for
    //!     the rationale.
    // -----------------------------------------------------------------------

    timer &             operator =( timer const & ) = delete ;

    typedef typename Device::duration_type
                        duration_type ;

    enum start_mode { auto_start, manual_start } ;

    //!     Initializes the underlying device by calling the default
    //!     constructor and, if (and only if) `mode == auto_start`,
    //!     calls start().
    // -----------------------------------------------------------------------
    explicit            timer( start_mode mode = auto_start ) ;

    //!     Calls `%start()` on the underlying `Device`.
    // -----------------------------------------------------------------------
    void                start() ;

    //!     \return
    //!         The result of calling `%elapsed()` on the underlying
    //!         `Device`.
    // -----------------------------------------------------------------------
    duration_type       elapsed() const ;

    //!     \return
    //!         The result of calling `%resolution()` on the underlying
    //!         `Device`.
    // -----------------------------------------------------------------------
    duration_type       resolution() const ;

private:
    Device              m_device ;
} ;

}

#include "brz/timer.tpp"
#endif
