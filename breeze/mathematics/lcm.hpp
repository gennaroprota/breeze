// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Returns the least common multiple of two integers.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_OFEP2tStNzXnzGYEV6JdW1XUXcS6lA7p
#define BREEZE_GUARD_OFEP2tStNzXnzGYEV6JdW1XUXcS6lA7p

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//      lcm():
//      ======
//
//!     \copybrief lcm.hpp
//!
//!     If \c T is not an integral type the program is ill-formed. If
//!     the least common multiple of \c |a| and \c |b| is not
//!     representable as a value of type \c T, the behavior is
//!     undefined.
//!
//!     \return
//!         If either \c a or \c b is zero, returns zero. Otherwise it
//!         returns the least common multiple of \c |a| and \c |b|.
//!
//!     \note
//!         This template diverges from the C++17 specification for the
//!         same reason why \c breeze::gcd() does.
//!
//!     \see
//!         gcd().
// ---------------------------------------------------------------------------
template< typename T >
constexpr T         lcm( T a, T b ) ;

}

#include "brz/lcm.tpp"
#endif
