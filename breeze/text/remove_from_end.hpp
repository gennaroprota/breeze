// ===========================================================================
//                        Copyright 2013 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Removes a `std::string` or a character from the end of a
//!            `std::string`.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_vf6LuqjTQ9wAJWXZsNnALWlVf4PYtieN
#define BREEZE_GUARD_vf6LuqjTQ9wAJWXZsNnALWlVf4PYtieN

#include "breeze/top_level_namespace.hpp"
#include <string>

namespace breeze_ns {

//      remove_from_end():
//      ==================
//
//!\brief
//!     Removes a given string from the end of another one.
//!
//!     \return
//!         If `s` ends with `to_be_removed`, `s` with the
//!         `to_be_removed` part erased from its end; otherwise a copy
//!         of `s`.
// ---------------------------------------------------------------------------
std::string         remove_from_end( std::string const & s,
                                     std::string const & to_be_removed ) ;

//      remove_from_end():
//      ==================
//
//!\brief
//!     Removes a given character from the end of a string.
//!
//!     \return
//!         If `s` ends with `c`, `s` with the last character removed;
//!         otherwise a copy of `s`.
// ---------------------------------------------------------------------------
std::string         remove_from_end( std::string const & s,
                                     char c ) ;
}

#endif
