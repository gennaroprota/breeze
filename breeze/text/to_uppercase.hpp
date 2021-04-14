// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Converts a string to uppercase (with 1:1 mapping).
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_R1GRWLUDyqEnauvYcedtZ5Pzz3Tx51As
#define BREEZE_GUARD_R1GRWLUDyqEnauvYcedtZ5Pzz3Tx51As

#include "breeze/top_level_namespace.hpp"
#include <locale>
#include <string>

namespace breeze_ns {

//      to_uppercase():
//      ---------------
//
//!     \copybrief to_uppercase.hpp
//!
//!     Converts each character in `source` to uppercase, using the
//!     `ctype` facet of the given locale. Only 1:1 character mapping
//!     can be performed: for instance it cannot convert the German
//!     Eszett to "SS".
//!
//!     \par Naming rationale
//!
//!     See the documentation of `to_lowercase()`.
//!
//!     \see
//!         to_lowercase().
// ---------------------------------------------------------------------------
std::string         to_uppercase( std::string const & source,
                                  std::locale const & loc = std::locale() ) ;

}

#endif
