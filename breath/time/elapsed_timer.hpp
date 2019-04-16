// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A policy based timer class (class template).
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_Jr0D8xlNtWxnToeomoet20V4lz0qIYDd
#define BREATH_GUARD_Jr0D8xlNtWxnToeomoet20V4lz0qIYDd

namespace breath {

//      elapsed_timer:
//      ==============
//
//!     A policy based timer which allows the user to retrieve the
//!     amount of time elapsed from its start.
//!
//!     \c Device is a policy modeling the "clock device" concept: this
//!     can be a hardware device, a network time provider, a GPS system
//!     or pretty much anything else. It must provide the member
//!     functions:
//!
//!      - \c restart()
//!      - \c elapsed()
//!      - \c resolution()
//!
//!     and the typedef
//!
//!      - \c duration_type
// ---------------------------------------------------------------------------
template< class Device >
class elapsed_timer
{
public:
    typedef typename Device::duration_type
                        duration_type ;

    enum start_mode { auto_start, manual_start } ;

    //!     Initializes the underlying device and, if <code>mode ==
    //!     auto_start</code> calls \c restart().
    // -----------------------------------------------------------------------
    explicit            elapsed_timer( start_mode mode = auto_start ) ;

    //!     Starts or restarts the timer. See \c elapsed().
    // -----------------------------------------------------------------------
    void                restart() ;

    //!     \return
    //!         The amount of time elapsed from the last call to \c
    //!         restart(). TODO gps: unit of measure.
    // -----------------------------------------------------------------------
    duration_type       elapsed() const ;

    //!     \return
    //!         The resolution of the timer, i.e. the smallest amount of
    //!         time that it can measure.
    // -----------------------------------------------------------------------
    duration_type       resolution() const ;

private:
    Device m_device ;
} ;

}

#include "brt/elapsed_timer.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
