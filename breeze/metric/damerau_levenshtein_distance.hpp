// ===========================================================================
//                        Copyright 2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Damerau-Levenshtein distance between two strings.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_DdgXuNwmaHGONiwKca8ikqBoDHQThmMu
#define BREEZE_GUARD_DdgXuNwmaHGONiwKca8ikqBoDHQThmMu

#include "breeze/top_level_namespace.hpp"
#include <cstddef>
#include <string>

namespace breeze_ns {

//      damerau_levenshtein_distance():
//      ===============================
//
//!     \return
//!         The Damerau-Levenshtein distance between \c first and
//!         \c second.
//!
//!     \pre
//!         The lengths of \c first and \c second are both less than
//!         \c PTRDIFF_MAX.
// ---------------------------------------------------------------------------
std::ptrdiff_t      damerau_levenshtein_distance( std::string const & first,
                                                  std::string const & second ) ;

}

#endif
