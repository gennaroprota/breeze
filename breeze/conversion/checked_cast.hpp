// ===========================================================================
//                        Copyright 2021 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Converts between integral types, with range checking.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_dSxX3rVQBYBO6sKuxmVMVnik5e6f9qec
#define BREEZE_GUARD_dSxX3rVQBYBO6sKuxmVMVnik5e6f9qec

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//      checked_cast():
//      ===============
//
//!     \copybrief checked_cast.hpp
//!
//!     checked_cast() converts a value of type `From` to type `To`,
//!     checking with BREEZE_ASSERT() that the source value is in range
//!     for the type `To`. If the value is in range, it returns the
//!     result of `static_cast< To >( from )`; otherwise an assertion is
//!     triggered.
//!
//!
//!     `To` and `From` must be types for which
//!     `std::numeric_limits::is_integer` is true; otherwise the program
//!     is ill-formed.
// ---------------------------------------------------------------------------
template< typename To, typename From >
constexpr To        checked_cast( From from ) ;

}

#include "brz/checked_cast.tpp"
#endif
