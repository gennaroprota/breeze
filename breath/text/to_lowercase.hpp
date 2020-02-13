// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Converts a string to lowercase (with 1:1 mapping).
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_dA64mnuy6S9Vw8QrcECul6ideTiRj7wi
#define BREATH_GUARD_dA64mnuy6S9Vw8QrcECul6ideTiRj7wi

#include <locale>
#include <string>

namespace breath {

//      to_lowercase():
//      ----------------
//
//!     Converts each character in \c source to lowercase, using the \c
//!     ctype facet of the given locale. Only 1:1 character mapping can
//!     be performed: for instance, the uppercase Greek letter sigma has
//!     two lowercase forms, which are chosen depending on whether they
//!     are the final letter of a word or not; this function cannot
//!     handle this.
//!
//!     Naming rationale:
//!     -----------------
//!
//!     I was a bit hesitant between the names "to_lower_case" and
//!     "to_lowercase". The issue is being consistent in the
//!     documentation: separating "lower" and "case" would mean using a
//!     space between the two words for usage as a noun, and a hyphen,
//!     instead, for usage as an adjective. This is error-prone.
//!     So I decided to use the spelling "lowercase" everywhere: code
//!     and documentation.
//!
//!     This is also consistent with the stream manipulator \c
//!     std::uppercase.
//!
//!     \see
//!         to_uppercase()
// ---------------------------------------------------------------------------
std::string         to_lowercase( std::string const & source,
                                  std::locale const & loc = std::locale() ) ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
