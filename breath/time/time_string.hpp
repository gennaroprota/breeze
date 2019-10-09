// ===========================================================================
//                        Copyright 2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A thin wrapper around \c std::strftime().
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_wR9yYhDtICLHOJ6c2LmBkhMWoYoaeVkS
#define BREATH_GUARD_wR9yYhDtICLHOJ6c2LmBkhMWoYoaeVkS

#include "breath/idiom/maybe.hpp"
#include <string>

namespace breath {

//      time_string_zone:
//      =================
//
//!     The type of timezone (UTC/local) in which the time must be
//!     returned.
// ---------------------------------------------------------------------------
class time_string_zone
{
public:
    enum zone
    {
        utc,
        local
    } ;

} ;


//      time_string():
//      ==============
//
//!     \return
//!         The current date and time formatted according to \c format,
//!         interpreted as if passed to the \c strftime() standard
//!         function. See also: time_string_zone.
//!
//!     This is a simple tool for simple and quick formatting needs.
//!     You should use a more complete solution for more complex needs
//!     (but don't underestimate the good old strftime() ;-)).
//!
//!     NOTE:
//!         this function is thread-safe and reentrant.
// ---------------------------------------------------------------------------
breath::maybe< std::string >
                    time_string( std::string const & format,
                                 time_string_zone::zone =
                                                    time_string_zone::utc ) ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
