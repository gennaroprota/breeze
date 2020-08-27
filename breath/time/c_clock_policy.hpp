// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A timer policy using \c std::clock().
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_s9RhTgkTQviSRQ89lVvZRW16hRqlr1OA
#define BREATH_GUARD_s9RhTgkTQviSRQ89lVvZRW16hRqlr1OA

#include "breath/top_level_namespace.hpp"
#include <ctime>

namespace breath_ns {

//      c_clock_policy:
//      ===============
//
//!     Note that on some (non-conforming) implementations
//!     std::clock() will actually measure wall-clock time.
//!
//!     One such implementation is the Microsoft one:
//!
//!    <https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/clock>.
// ---------------------------------------------------------------------------
class c_clock_policy
{
public:
    typedef long double duration_type ;

    //!     Leaves this object in an undefined state. The only action
    //!     that can be performed on a just constructed object is to
    //!     call start().
    // -----------------------------------------------------------------------
                        c_clock_policy() ;

    //!     \throw
    //!         A \c std::runtime_error if \c std::clock() fails.
    // -----------------------------------------------------------------------
    void                start() ;

    //!     \return
    //!         The time, in milliseconds, elapsed from the last
    //!         (re)start.
    //!
    //!     \pre
    //!         The function start() has been called at least once.
    //!
    //!     \throw
    //!         A \c std::runtime_error if it detects wrap-around (it
    //!         only detects \e some wrap-arounds), or if \c
    //!         std::clock() fails.
    // -----------------------------------------------------------------------
    duration_type       elapsed() const ;

    //!     \return
    //!         An estimate of the timer resolution, in milliseconds.
    //!         May return slightly different values from call to call.
    //!
    //!     \throw
    //!         A \c std::runtime_error if it detects wrap-around (it
    //!         only detects \e some wrap-arounds), or if \c
    //!         std::clock() fails.
    // -----------------------------------------------------------------------
    duration_type       resolution() const ;

private:
    std::clock_t        m_start_tick ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
