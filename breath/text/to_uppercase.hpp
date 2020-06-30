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

#ifndef BREATH_GUARD_R1GRWLUDyqEnauvYcedtZ5Pzz3Tx51As
#define BREATH_GUARD_R1GRWLUDyqEnauvYcedtZ5Pzz3Tx51As

#include "breath/top_level_namespace.hpp"
#include <locale>
#include <string>

namespace breath_ns {

//      to_uppercase():
//      ---------------
//
//!     Converts each character in \c source to uppercase, using the \c
//!     ctype facet of the given locale. Only 1:1 character mapping can
//!     be performed: for instance it cannot convert the German Eszett
//!     to "SS".
//!
//!     Naming rationale:
//!     -----------------
//!
//!     See the documentation of \c to_lowercase().
//!
//!     \see
//!         to_lowercase()
// ---------------------------------------------------------------------------
std::string         to_uppercase( std::string const & source,
                                  std::locale const & loc = std::locale() ) ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
