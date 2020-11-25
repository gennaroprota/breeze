// ===========================================================================
//                     Copyright 2016-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A \c std::string trimmer.
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
//!     \return
//!         A string obtained from \c str by removing all the leading
//!         and all the trailing characters \c c for which <code>
//!         std::isspace( c, loc )</code> returns \c true.
// ---------------------------------------------------------------------------
std::string         trim( std::string const & str, std::locale const & loc ) ;

//      trim():
//      =======
//
//!     \return
//!         A string obtained from \c str by removing all the leading
//!         and all the trailing characters that are also contained in
//!         \c to_remove.
// ---------------------------------------------------------------------------
std::string         trim( std::string const &  str,
                          set_of_chars const & to_remove ) ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
