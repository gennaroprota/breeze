// ===========================================================================
//                     Copyright 2013-2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Returns whether a string ends with a given string, or a
//!            given character.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_FXhivw6tI6cV0C3govXyzZBmNCWa1e2o
#define BREEZE_GUARD_FXhivw6tI6cV0C3govXyzZBmNCWa1e2o

#include "breeze/top_level_namespace.hpp"
#include <string>

namespace breeze_ns {

//      ends_with():
//      ============
//
//!\brief
//!     Checks whether `s` ends with `with`.
//!
//!     If `with` is empty, the result is always `true`.
//!
//!     \note
//!         [FUTURE] C++20 will have
//!           `std::basic_string::ends_with()` and
//!           `std::basic_string_view::ends_with()`
//!         for this.
//!
//!     \see
//!         begins_with().
// ---------------------------------------------------------------------------
bool                ends_with( std::string const & s,
                               std::string const & with ) noexcept ;

//      ends_with():
//      ============
//
//!\brief
//!     Checks whether `s` ends with `c`.
//!
//!     \return
//!         `true` if and only if `s` ends with `c`, i.e. if and only if
//!         `! s.empty() && s.back() == c`.
// ---------------------------------------------------------------------------
bool                ends_with( std::string const & s,
                               char c )                   noexcept ;

}

#endif
