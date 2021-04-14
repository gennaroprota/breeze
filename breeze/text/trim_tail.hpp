// ===========================================================================
//                     Copyright 2008-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Trims the tail of a `std::string`.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_rAf6FomrfEupsrKlsZvh9xwbNaeg8pxp
#define BREEZE_GUARD_rAf6FomrfEupsrKlsZvh9xwbNaeg8pxp

#include "breeze/top_level_namespace.hpp"
#include "breeze/text/set_of_chars.hpp"
#include <locale>
#include <string>

namespace breeze_ns {

//      trim_tail():
//      ============
//
//!     \copybrief trim_tail.hpp
//!
//!     \return
//!         A string obtained from `s` by removing all the trailing
//!         characters `c` for which `std::isspace( c, loc )` returns
//!         `true`.
// ---------------------------------------------------------------------------
std::string         trim_tail( std::string const & s,
                               std::locale const & loc = std::locale() ) ;

//      trim_tail():
//      ============
//
//!     \copybrief trim_tail.hpp
//!
//!     \return
//!         A string obtained from `s` by removing all the trailing
//!         characters that are also contained in `to_be_removed`.
// ---------------------------------------------------------------------------
std::string         trim_tail( std::string const &  s,
                               set_of_chars const & to_be_removed ) ;

}

#endif
