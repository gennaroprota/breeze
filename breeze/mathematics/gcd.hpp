// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Returns the greatest common divisor of two integers.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_7TolwuFfch2xrqOdKkP8IrjIejdJYQxs
#define BREEZE_GUARD_7TolwuFfch2xrqOdKkP8IrjIejdJYQxs

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//      gcd():
//      ======
//
//!     \copybrief gcd.hpp
//!
//!     If \c T is not an integral type the program is ill-formed. If
//!     the greatest common divisor of \c |a| and \c |b| is not
//!     representable as a value of type \c T, the behavior is
//!     undefined.
//!
//!     \return
//!         If both \c a and \c b are zero, returns zero. Otherwise it
//!         returns the greatest common divisor of \c |a| and \c |b|.
//!
//!     \note
//!         The intent, for both this template and \c breeze::lcm(), was
//!         to follow the standard specification (the initial Breeze
//!         versions followed the C++ Library Fundamental TS v2, and I
//!         meant to update them to C++17 when C++17 would be out). But
//!         I soon realized that allowing two different types for the
//!         two arguments, and using \c common_type for the result, made
//!         everything very hard to reason about (can you tell what the
//!         \c common_type of two arbitrary integral types is?). So I
//!         decided to stick to what I consider a saner specification.
//!
//!     \see
//!         lcm()
// ---------------------------------------------------------------------------
template< typename T >
constexpr T         gcd( T a, T b ) ;

}

#include "brz/gcd.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
