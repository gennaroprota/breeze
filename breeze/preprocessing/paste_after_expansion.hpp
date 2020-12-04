// ===========================================================================
//                     Copyright 2008-2013 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A token concatenation macro.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_TtY9fvceSS7uDBmVi38DjzXQQYbGSOLw
#define BREEZE_GUARD_TtY9fvceSS7uDBmVi38DjzXQQYbGSOLw

#include "breeze/preprocessing/paste.hpp"

//      BREEZE_PASTE_AFTER_EXPANSION():
//      ===============================
//
//!     Applies BREEZE_PASTE() to the result of performing macro
//!     replacement on the arguments \c x and \c y.
//!
//!     See BREEZE_PASTE() for the naming rationale.
// ---------------------------------------------------------------------------
#define BREEZE_PASTE_AFTER_EXPANSION( x, y )    BREEZE_PASTE( x, y )

#endif
