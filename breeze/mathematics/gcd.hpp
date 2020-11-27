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
#include <type_traits>

namespace breeze_ns {

//      gcd():
//      ======
//
//!     \copybrief gcd.hpp
//!
//!     This template follows the C++ Library Fundamental TS v2, as of
//!     May 14, 2016.
//!
//!     If either \c M or \c N is not an integral type the program is
//!     ill-formed. If \c |m| is not representable as a value of type \c
//!     M or \c |n| is not representable as a value of type \c N, the
//!     behavior is undefined.
//!
//!     \return
//!         If both \c m and \c n are zero, returns zero. Otherwise it
//!         returns the greatest common divisor of \c |m| and \c |n|.
//!
//!     \see
//!         lcm()
// ---------------------------------------------------------------------------
template< typename M, typename N >
constexpr std::common_type_t< M, N >
                    gcd( M m, N n ) ;

}

#include "brz/gcd.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
