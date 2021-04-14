// ===========================================================================
//                     Copyright 2006-2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Thin wrapper around `std::getenv()`.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_DJJ43p6UR3Ib7dPq3Qi3OoGCOlpQ0iRV
#define BREEZE_GUARD_DJJ43p6UR3Ib7dPq3Qi3OoGCOlpQ0iRV

#include "breeze/top_level_namespace.hpp"
#include "breeze/vocabulary/maybe.hpp"
#include <string>

namespace breeze_ns {

//      get_environment_variable():
//      ===========================
//
//!\brief
//!     Retrieves an environment variable.
//!
//!     Searches an implementation-defined list, as if by calling
//!     `std::getenv()`, for a string that matches `name` and returns
//!     the associated value, if any.
//!
//!     We emphasize that the 'as if' above is part of this function's
//!     contract.
//!
//!     This function overcomes three usability issues of
//!     `std::getenv()`:
//!
//!      - const unsafety: `getenv()` returns a pointer to (non-const)
//!        char (which the program shall not modify)
//!
//!      - subsequent calls to `getenv()` may overwrite the pointed to
//!        string
//!
//!      - if the searched to string is not found `getenv()` returns a
//!        null pointer; that can easily lead to undefined behavior, if
//!        that value is passed to one of the constructors of
//!        `std::string` which take a `char const *`
//!
//!     \return
//!         The value associated to the given `name`, or an invalid
//!         `maybe` if there is none.
//!
//!     \note
//!         The behavior on passing an empty string for the `name`
//!         parameter is implementation-defined: please check the
//!         documentation provided with your C++ implementation.
// ---------------------------------------------------------------------------
maybe< std::string >
                    get_environment_variable( std::string const & name ) ;

}

#endif
