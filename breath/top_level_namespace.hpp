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

#ifndef BREATH_GUARD_MhCkUzxL3N7xf6WLWCGn46w95N2ucEni
#define BREATH_GUARD_MhCkUzxL3N7xf6WLWCGn46w95N2ucEni

#include "breath/preprocessing/paste_after_expansion.hpp"
#include "breath/version.hpp"


//      breath_ns:
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
//!     Client code must not use this name, but the "normal" name \c
//!     breath, which is defined as an alias to the versioned name.
//!
//!     Once again, I got this idea from James.
// ---------------------------------------------------------------------------
#define breath_ns BREATH_PASTE_AFTER_EXPANSION( breath_, BREATH_VERSION )

namespace breath_ns {

}

namespace breath = breath_ns ;

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
