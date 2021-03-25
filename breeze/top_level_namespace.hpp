// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief This file is for internal use only.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_MhCkUzxL3N7xf6WLWCGn46w95N2ucEni
#define BREEZE_GUARD_MhCkUzxL3N7xf6WLWCGn46w95N2ucEni

#include "breeze/preprocessing/paste_after_expansion.hpp"
#include "breeze/version.hpp"


//      breeze_ns:
//      ==========
//
//!     \hideinitializer
//!
//!     Expands to the name of the top-level namespace used internally
//!     by the library.
//!
//!     The name integrates the library version, so that code compiled
//!     against a given version of the library will not link against a
//!     different version.
//!
//!     Client code must not use this name, but the "normal" name
//!     `breeze`, which is defined as an alias to the versioned name.
//!
//!     Once again, I got this idea from James.
// ---------------------------------------------------------------------------
#define breeze_ns BREEZE_PASTE_AFTER_EXPANSION( breeze_, BREEZE_VERSION )

namespace breeze_ns {

}

namespace breeze = breeze_ns ;

#endif
