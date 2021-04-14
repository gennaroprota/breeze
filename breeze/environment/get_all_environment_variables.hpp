// ===========================================================================
//                        Copyright 2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Gets a map with all the environment variables and their
//!            values.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_U4BCWO9huCRrS51C9yYWQld0Ixzmwe5L
#define BREEZE_GUARD_U4BCWO9huCRrS51C9yYWQld0Ixzmwe5L

#include "breeze/top_level_namespace.hpp"
#include <map>
#include <string>

namespace breeze_ns {

//      get_all_environment_variables():
//      ================================
//
//!\brief
//!     Retrieves all the environment variables.
//!
//!     \return
//!         A map with all name-value pairs corresponding to the defined
//!         environment variables.
//!
//!     \par Exceptions
//!         A `std::runtime_error` if an error occurs. TODO: document
//!         exceptions for allocation errors?
// ---------------------------------------------------------------------------
std::map< std::string, std::string >
                    get_all_environment_variables() ;

}

#endif
