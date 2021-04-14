// ===========================================================================
//                     Copyright 2008-2013 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Stringizing macro.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_oC4DKLgCzbQ7cdHjPg7UM8ShKNKAc32G
#define BREEZE_GUARD_oC4DKLgCzbQ7cdHjPg7UM8ShKNKAc32G

#include "breeze/preprocessing/stringize.hpp"

//      BREEZE_STRINGIZE_AFTER_EXPANSION():
//      ===================================
//
//!\brief
//!     Stringizes preprocessing tokens after macro expansion.
//!
//!     Stringizes (with `BREEZE_STRINGIZE()`) the result of performing
//!     macro replacement on the argument `x`.
// ---------------------------------------------------------------------------
#define BREEZE_STRINGIZE_AFTER_EXPANSION( x )   BREEZE_STRINGIZE( x )

#endif
