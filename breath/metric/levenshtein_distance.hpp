// ===========================================================================
//                        Copyright 2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Levenshtein distance between two strings.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_VVpm0oaMKolmpySje2Hc9KAsKdaGIZSb
#define BREATH_GUARD_VVpm0oaMKolmpySje2Hc9KAsKdaGIZSb

#include <cstddef>
#include <string>

namespace breath {

//      levenshtein_distance():
//      =======================
//
//!     \return
//!         The Levenshtein distance between \c first and \c second.
// ---------------------------------------------------------------------------
std::size_t         levenshtein_distance( std::string const & first,
                                          std::string const & second ) ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
