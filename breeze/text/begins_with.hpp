// ===========================================================================
//                     Copyright 2013-2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Returns whether a string begins with another one.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_pjj1lvDnitxdxtZbFZ64jGnnUhPhHABq
#define BREEZE_GUARD_pjj1lvDnitxdxtZbFZ64jGnnUhPhHABq

#include "breeze/top_level_namespace.hpp"
#include <string>

namespace breeze_ns {

//!     \return
//!         Whether \c str begins with \c with. If \c with is empty, the
//!         result is always \c true.
//!
//!     \note
//!         [FUTURE] C++20 will have
//!           <code>std::basic_string::starts_with()</code> and
//!           <code>std::basic_string_view::starts_with()</code>
//!         for this.
//!
//!     \see
//!         ends_with()
// ---------------------------------------------------------------------------
bool                begins_with( std::string const & str,
                                 std::string const & with ) noexcept ;

}

#endif
