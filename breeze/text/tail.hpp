// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Returns the tail of a string.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_48671WeJXu9JNdXpT04IlPYpPx1GCY0K
#define BREEZE_GUARD_48671WeJXu9JNdXpT04IlPYpPx1GCY0K

#include "breeze/top_level_namespace.hpp"
#include <cstddef>
#include <string>

namespace breeze_ns {

//      tail():
//      =======
//
//!     \pre
//!         count >= 0
//!
//!     \return
//!         If `count >= s.length()`, `s`; otherwise the string composed
//!         of the last `count` characters of `s` (an empty string if
//!         `count == 0`).
// ---------------------------------------------------------------------------
std::string         tail( std::string const & s, std::ptrdiff_t count ) ;

}

#endif
