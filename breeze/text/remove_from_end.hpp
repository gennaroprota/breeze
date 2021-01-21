// ===========================================================================
//                        Copyright 2013 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Removes a \c std::string from the end of a \c
//!            std::string.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_vf6LuqjTQ9wAJWXZsNnALWlVf4PYtieN
#define BREEZE_GUARD_vf6LuqjTQ9wAJWXZsNnALWlVf4PYtieN

#include "breeze/top_level_namespace.hpp"
#include <string>

namespace breeze_ns {

//      remove_from_end():
//      ==================
//
//!     \return
//!         If \c str ends with \c to_be_removed, \c str with the
//!         \c to_be_removed part erased from its end; otherwise
//!         a copy of \c str.
// ---------------------------------------------------------------------------
std::string         remove_from_end( std::string const & str,
                                     std::string const & to_be_removed ) ;

//      remove_from_end():
//      ==================
//
//!     \return
//!         If \c str ends with \c c, \c str with the last character
//!         removed; otherwise a copy of \c str.
// ---------------------------------------------------------------------------
std::string         remove_from_end( std::string const & str,
                                     char c ) ;
}

#endif
