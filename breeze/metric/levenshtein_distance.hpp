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

#ifndef BREEZE_GUARD_VVpm0oaMKolmpySje2Hc9KAsKdaGIZSb
#define BREEZE_GUARD_VVpm0oaMKolmpySje2Hc9KAsKdaGIZSb

#include "breeze/top_level_namespace.hpp"
#include <cstddef>
#include <string>

namespace breeze_ns {

//      levenshtein_distance():
//      =======================
//
//!\brief
//!     Returns the Levenshtein distance between `first` and `second`.
// ---------------------------------------------------------------------------
std::ptrdiff_t      levenshtein_distance( std::string const & first,
                                          std::string const & second ) ;

}

#endif
