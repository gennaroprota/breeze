// ===========================================================================
//                     Copyright 2015-2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Returns the allowed directory separators in the running
//!            system.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_bvA1h6sHG51DDAzrkOaJBHIxlZBpgVnA
#define BREATH_GUARD_bvA1h6sHG51DDAzrkOaJBHIxlZBpgVnA

#include "breath/top_level_namespace.hpp"

namespace breath_ns {

//      directory_separators():
//      =======================
//
//!     \return
//!         A pointer to a C string with static lifetime containing the
//!         directory separators allowed in the system.
//!
//!         If a "preferred" separator exists, it is guaranteed to be
//!         the first character of the string.
// ---------------------------------------------------------------------------
char const *        directory_separators() noexcept ; //gps constexpr?

}
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
