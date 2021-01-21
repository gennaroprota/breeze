// ===========================================================================
//                     Copyright 2008-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A \c std::string trimmer (tail of string).
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
//!     \return
//!         A string obtained from \c s by removing all the trailing
//!         characters \c c for which <code>std::isspace( c, loc )
//!         </code> returns \c true.
// ---------------------------------------------------------------------------
std::string         trim_tail( std::string const & s,
                               std::locale const & loc = std::locale() ) ;

//      trim_tail():
//      ============
//
//!     \return
//!         A string obtained from \c s by removing all the trailing
//!         characters that are also contained in \c to_be_removed.
// ---------------------------------------------------------------------------
std::string         trim_tail( std::string const &  s,
                               set_of_chars const & to_be_removed ) ;

}

#endif
