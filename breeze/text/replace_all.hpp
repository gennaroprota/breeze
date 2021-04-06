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
//!     \return
//!         A string obtained from `original` by replacing all
//!         occurrences of `from` with `to`.
//!
//!     \throw
//!         `length_error`
//!
//!     \pre
//!         ! from.empty()
//!
//!     Note that `to` can be empty; so, as a special case, this
//!     function can *remove* all occurrences of a substring.
// ---------------------------------------------------------------------------
std::string         replace_all(
    std::string const & original,
    std::string const & from,
    std::string const & to ) ;

}

#endif
