// ===========================================================================
//                     Copyright 2011-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A \c std::string trimmer (head of string).
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
//!     \return
//!         A string obtained from \c str by removing all the leading
//!         characters \c c for which <code>std::isspace( c, loc )
//!         </code> returns \c true.
// ---------------------------------------------------------------------------
std::string         trim_head( std::string const & str,
                               std::locale const & loc = std::locale() ) ;

//      trim_head():
//      ============
//
//!     \return
//!         A string obtained from \c str by removing all the leading
//!         characters that are also contained in \c to_remove.
// ---------------------------------------------------------------------------
std::string         trim_head( std::string const &  str,
                               set_of_chars const & to_remove ) ;
}

#endif
