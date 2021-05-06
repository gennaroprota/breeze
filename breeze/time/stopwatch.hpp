// ===========================================================================
//                     Copyright 2006-2021 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A policy-based stopwatch class (class template).
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_Jr0D8xlNtWxnToeomoet20V4lz0qIYDd
#define BREEZE_GUARD_Jr0D8xlNtWxnToeomoet20V4lz0qIYDd

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//      stopwatch:
//      ==========
//
//!     \copybrief stopwatch.hpp
//!
//!     A policy-based stopwatch, i.e. a class template which allows
//!     retrieving the amount of time elapsed from its start.
//!
//!     `Clock` is a type that satisfies the <tt>Clock</tt> requirements
//!     (C++ standard, [time.clock.req]). This means that a `stopwatch`
//!     can be used e.g. with `std::system_clock`, `std::steady_clock`,
//!     or `std::gps_clock`. In addition, we provide clocks that use the
//!     C function `std::clock()` and, for Windows,
//!     `QueryPerformanceCounter()`.
//!
//!     It's the user's responsibility to check that the clock is
//!     steady, if needed.
//!
//!     Optionally, the `Clock` type may provide the \e static member
//!     function:
//!
//!      - `%resolution()`,
//!            which must return the resolution of the `Clock` or an
//!            estimate of it; note that the resolution is the smallest
//!            amount of time that the `Clock` can measure and doesn't,
//!            in itself, tell anything about the \e accuracy
//!
//!     This function is only used in `stopwatch::resolution()`, so if
//!     you don't need the latter, you can omit it.
// ---------------------------------------------------------------------------
template< class Clock >
class stopwatch
{
public:
    //!     A synonym of `Clock::duration`.
    // -----------------------------------------------------------------------
    using               duration = typename Clock::duration ;

    enum start_mode { auto_start, manual_start } ;

    //!     Deleted copy constructor.
    //!
    //!     \par Rationale
    //!
    //!     Specifying copy semantics for a stopwatch is a bit difficult
    //!     and, although it can probably be done, it's not worth it, as
    //!     who would copy a stopwatch, anyway? (A stopwatch will, in
    //!     practice, always be used like a Python context.)
    // -----------------------------------------------------------------------
                        stopwatch(  stopwatch const & ) = delete ;

    //!     Deleted copy assignment operator.
    //!
    //!     See the documentation of the (deleted) copy constructor for
    //!     the rationale.
    // -----------------------------------------------------------------------
    stopwatch &         operator =( stopwatch const & ) = delete ;

    //!     If `mode == auto_start`, calls start(); otherwise, it leaves
    //!     the stopwatch in an undefined state, in which the only
    //!     member functions that can be called are start() and the
    //!     destructor.
    // -----------------------------------------------------------------------
    explicit            stopwatch( start_mode mode = auto_start ) ;

    //!     Marks the start of a measurement.
    // -----------------------------------------------------------------------
    void                start() ;

    //!     \return
    //!         The amount of time elapsed from the last call to
    //!         start().
    // -----------------------------------------------------------------------
    duration            elapsed() const ;

    //!     \return
    //!         The result of calling `Clock::resolution()`.
    // -----------------------------------------------------------------------
    static duration     resolution() ;

private:
    using               time_point = typename Clock::time_point ;

    time_point          m_start_time ;
} ;

}

#include "brz/stopwatch.tpp"
#endif
