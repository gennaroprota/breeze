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
//!     Stringizes (with \c BREEZE_STRINGIZE()) the result of performing
//!     macro replacement on the argument \c x.
// ---------------------------------------------------------------------------
#define BREEZE_STRINGIZE_AFTER_EXPANSION( x )   BREEZE_STRINGIZE( x )

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
