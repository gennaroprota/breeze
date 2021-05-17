// ===========================================================================
//                     Copyright 2018-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief The representation of an integer in a given base.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_lqF1VhyaeQBA6t5SZLvv9rpFKK1iZVzu
#define BREEZE_GUARD_lqF1VhyaeQBA6t5SZLvv9rpFKK1iZVzu

#include "breeze/top_level_namespace.hpp"
#include <string>

namespace breeze_ns {

//!\brief
//!     Returns the representation, in base `base`, of the integer `n`.
//!
//!     \pre
//!         base >= 2 && base <= 36
//!
//!     A negative value is represented as the character '-' (minus)
//!     immediately followed by the representation of its absolute value
//!     (in the mathematical sense: the minimum value of `T` is handled
//!     correctly, even on a two's complement implementation).
// ---------------------------------------------------------------------------
template< typename T >
std::string         representation_in_base( T n, int base ) ;

}

#include "brz/representation_in_base.tpp"
#endif
