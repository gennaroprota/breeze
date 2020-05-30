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

#ifndef BREATH_GUARD_U4BCWO9huCRrS51C9yYWQld0Ixzmwe5L
#define BREATH_GUARD_U4BCWO9huCRrS51C9yYWQld0Ixzmwe5L

#include <map>
#include <string>

namespace breath {

//!     \return
//!         A map with all name-value pairs corresponding to the defined
//!         environment variables.
// ---------------------------------------------------------------------------
std::map< std::string, std::string >
                    get_all_environment_variables() ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
