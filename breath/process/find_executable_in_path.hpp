// ===========================================================================
//                        Copyright 2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Finds an executable file in a given path.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_FY2GqgDJYLYk2fqwzgZI8Nhxv6QAdsQW
#define BREATH_GUARD_FY2GqgDJYLYk2fqwzgZI8Nhxv6QAdsQW

#include "breath/idiom/maybe.hpp"
#include <string>

namespace breath {

//      find_executable_in_path():
//      ==========================
//
//!     Finds an executable file. If \c path.is_valid(), then the
//!     executable is searched in \c path.value(). Otherwise, it
//!     is searched in a system dependent list (\c PATH environment
//!     variable) and in the current working directory. It is
//!     unspecified whether the current working directory is searched
//!     before or after the directories in \c PATH.
//!
//!     \return
//!         A \c maybe< std::string > that is invalid (for failure) or
//!         contains the full path of the found executable.
// ---------------------------------------------------------------------------
maybe< std::string >
                    find_executable_in_path(
                        std::string const & name,
                        maybe< std::string > const & path =
                                                maybe< std::string >() ) ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
