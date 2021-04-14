// ===========================================================================
//                     Copyright 2016-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Trims a `std::string`.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_rws4wbvfhp1gTSnTPzZEhVe9JHM0Cwgk
#define BREEZE_GUARD_rws4wbvfhp1gTSnTPzZEhVe9JHM0Cwgk

#include "breeze/top_level_namespace.hpp"
#include <locale>
#include <string>

namespace breeze_ns {

class               set_of_chars ;

//      trim():
//      =======
//
//!     \copybrief trim.hpp
//!
//!     \return
//!         A string obtained from `s` by removing all the leading and
//!         all the trailing characters `c` for which `std::isspace( c,
//!         loc )` returns `true`.
// ---------------------------------------------------------------------------
std::string         trim( std::string const & s, std::locale const & loc ) ;

//      trim():
//      =======
//
//!     \copybrief trim.hpp
//!
//!     \return
//!         A string obtained from `s` by removing all the leading and
//!         all the trailing characters that are also contained in
//!         `to_be_removed`.
// ---------------------------------------------------------------------------
std::string         trim( std::string const &  s,
                          set_of_chars const & to_be_removed ) ;

}

#endif
