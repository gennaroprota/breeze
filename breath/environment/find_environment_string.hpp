// ===========================================================================
//                     Copyright 2006-2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Thin wrapper around \c std::getenv().
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_DJJ43p6UR3Ib7dPq3Qi3OoGCOlpQ0iRV
#define BREATH_GUARD_DJJ43p6UR3Ib7dPq3Qi3OoGCOlpQ0iRV

#include "breath/idiom/maybe.hpp"
#include <string>

namespace breath {

//      find_environment_string():
//      ==========================
//
//!     Searches an implementation-defined list, as if by calling
//!     \c std::getenv(), for a string that matches \c name.
//!
//!     We emphasize that the 'as if' above is part of this function's
//!     contract.
//!
//!     This function overcomes three usability issues of \c
//!     std::getenv():
//!
//!      - const unsafety: \c getenv() returns a pointer to (non const)
//!        char (which the program shall not modify)
//!
//!      - subsequent calls to \c getenv() may overwrite the pointed to
//!        string
//!
//!      - if the searched to string is not found \c getenv() returns a
//!        null pointer; that can easily lead to undefined behavior,
//!        if that value is passed to one of the constructors of
//!        \c std::string which take a <code>char const *</code>
//!
//!     \note
//!         The behavior on passing an empty string for the \c name
//!         parameter is implementation-defined: please check the
//!         documentation provided with your C++ implementation.
// ---------------------------------------------------------------------------
maybe< std::string >
                    find_environment_string( std::string const & name ) ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
