// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A macro to prevent expansion of other macros.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_KezEcitYEJtdq09HtWJssCKDNm4sXaV5
#define BREEZE_GUARD_KezEcitYEJtdq09HtWJssCKDNm4sXaV5

//      BREEZE_PREVENT_MACRO_EXPANSION:
//      ===============================
//
//!     The only purpose of this macro is to prevent the expansion of
//!     the preceding identifier, in case it is defined as a
//!     function-like macro. Any macro would do (in fact, anything which
//!     isn't an open paren), but this has a self-documenting name.
//!
//!     Typically used for the identifiers `min` and `max`. Example:
//!
//!     ```
//!         int const           m =
//!          std::numeric_limits< int >::max BREEZE_PREVENT_MACRO_EXPANSION () ;
//!     ```
//!
//!     Note that you can prevent macro substitution by enclosing the
//!     offending name in parentheses, but that also inhibits ADL,
//!     whereas this macro has absolutely no effect in that regard.
// ---------------------------------------------------------------------------
#define BREEZE_PREVENT_MACRO_EXPANSION

#endif
