// ===========================================================================
//                        Copyright 2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Digital root of a (non-negative) integer.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_XtTcG5ymuoVaWgnKITP3OQP7ggHKE44e
#define BREEZE_GUARD_XtTcG5ymuoVaWgnKITP3OQP7ggHKE44e

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//      digital_root():
//      ===============
//
//!\brief
//!     Returns the digital root of the number `n` in base `base`.
//!
//!     \pre
//!         n >= 0 && base >= 2
// ---------------------------------------------------------------------------
template< typename T >
constexpr int       digital_root( T n, int base = 10 ) ;

}

#include "brz/digital_root.tpp"
#endif
