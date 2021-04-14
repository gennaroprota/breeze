// ===========================================================================
//                     Copyright 2011-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Trims the head of a `std::string`.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_VJhjD7vyKemLfcukUGXm4RzXGSsdvmrL
#define BREEZE_GUARD_VJhjD7vyKemLfcukUGXm4RzXGSsdvmrL

#include "breeze/top_level_namespace.hpp"
#include "breeze/text/set_of_chars.hpp"
#include <locale>
#include <string>

namespace breeze_ns {

//      trim_head():
//      ============
//
//!     \copybrief trim_head.hpp
//!
//!     \return
//!         A string obtained from `s` by removing all the leading
//!         characters `c` for which `std::isspace( c, loc )` returns
//!         `true`.
// ---------------------------------------------------------------------------
std::string         trim_head( std::string const & s,
                               std::locale const & loc = std::locale() ) ;

//      trim_head():
//      ============
//
//!     \copybrief trim_head.hpp
//!
//!     \return
//!         A string obtained from `s` by removing all the leading
//!         characters that are also contained in `to_be_removed`.
// ---------------------------------------------------------------------------
std::string         trim_head( std::string const &  s,
                               set_of_chars const & to_be_removed ) ;
}

#endif
