// ===========================================================================
//                     Copyright 2013-2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Returns whether a string begins with a given string, or a
//!            given character.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_pjj1lvDnitxdxtZbFZ64jGnnUhPhHABq
#define BREEZE_GUARD_pjj1lvDnitxdxtZbFZ64jGnnUhPhHABq

#include "breeze/top_level_namespace.hpp"
#include <string>

namespace breeze_ns {

//      begins_with():
//      ==============
//
//!\brief
//!     Checks whether `s` begins with `with`.
//!
//!     If `with` is empty, the result is always `true`.
//!
//!     \note
//!         [FUTURE] C++20 will have
//!           `std::basic_string::starts_with()` and
//!           `std::basic_string_view::starts_with()`
//!         for this.
//!
//!     \see
//!         ends_with().
// ---------------------------------------------------------------------------
bool                begins_with( std::string const & s,
                                 std::string const & with ) noexcept ;

//      begins_with():
//      ==============
//
//!\brief
//!     Checks whether `s` begins with `c`.
//!
//!     \return
//!         `true` if and only if `s` begins with `c`; i.e. if and only
//!         if `! s.empty() && s.front() == c`.
// ---------------------------------------------------------------------------
bool                begins_with( std::string const & s,
                                 char c )                   noexcept ;

}

#endif
