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

#ifndef BREATH_GUARD_oNNLAbfLiNCB1qfs0q2QLDtlsFTosyBu
#define BREATH_GUARD_oNNLAbfLiNCB1qfs0q2QLDtlsFTosyBu

#include <string>

namespace breath {

//      replace_all():
//      ==============
//
//!     Replaces all occurrences of \c from in \c s with \c to. May
//!     throw length_error (only if \c to is longer than \c from?).
//!
//!     \pre
//!         ! from.empty()
//!
//!     Note that \c to can be empty; so, as a special case, this
//!     function can *remove* all occurrences of a substring.
//!
//!     Rationale
//!     ---------
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

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
