// ===========================================================================
//                        Copyright 2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A function that replaces substrings.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_oNNLAbfLiNCB1qfs0q2QLDtlsFTosyBu
#define BREEZE_GUARD_oNNLAbfLiNCB1qfs0q2QLDtlsFTosyBu

#include "breeze/top_level_namespace.hpp"
#include <string>

namespace breeze_ns {

//      replace_all():
//      ==============
//
//!     Replaces all occurrences of `from` in `s` with `to`. May throw
//!     `length_error` (only if `to` is longer than `from`?).
//!
//!     \pre
//!         ! from.empty()
//!
//!     Note that `to` can be empty; so, as a special case, this
//!     function can *remove* all occurrences of a substring.
//!
//!     \par Rationale
//!
//!     This function modifies the string in place. A non-modifying
//!     version (replace_all_copy()) could be constructed in terms of
//!     this.
// ---------------------------------------------------------------------------
void                replace_all(
    std::string &       s,
    std::string const & from,
    std::string const & to ) ;

}

#endif
