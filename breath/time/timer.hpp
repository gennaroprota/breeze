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

//      timer:
//      ======
//
//!     A policy based timer which allows the user to retrieve the
//!     amount of time elapsed from its start.
//!
//!     \c Device is a policy modeling the "clock device" concept: this
//!     can be a hardware device, a network time provider, a GPS system
//!     or pretty much anything else. It must be \c DefaultConstructible
//!     and provide the member functions:
//!
//!      - \c %restart(),
//!            which must start or restart the \c Device
//!
//!      - \c %elapsed(),
//!            which must return the amount of time elapsed from the
//!            last call to \c %restart()
//!
//!      - \c %resolution(),
//!            which must return the resolution of the \c Device, i.e.
//!            the smallest amount of time it can measure
//!
//!     and the typedef
//!
//!      - \c duration_type,
//!            which is the return type of \c %elapsed() and
//!            \c %resolution()
// ---------------------------------------------------------------------------
template< class Device >
class timer
{
public:
    typedef typename Device::duration_type
                        duration_type ;

    enum start_mode { auto_start, manual_start } ;

    //!     Initializes the underlying device by calling the default
    //!     constructor and, if <code>mode == auto_start</code> calls
    //!     restart().
    // -----------------------------------------------------------------------
    explicit            timer( start_mode mode = auto_start ) ;

    //!     Calls Device::restart().
    // -----------------------------------------------------------------------
    void                restart() ;

    //!     \return
    //!         The result of calling %elapsed() on the underlying \c
    //!         Device.
    //!
    //!         TODO gps: unit of measure.
    // -----------------------------------------------------------------------
    duration_type       elapsed() const ;

    //!     \return
    //!         The result of calling Device::resolution().
    // -----------------------------------------------------------------------
    duration_type       resolution() const ;

private:
    Device m_device ;
} ;

}

#include "brt/timer.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
