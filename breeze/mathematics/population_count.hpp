// ===========================================================================
//                        Copyright 2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A simple bit counter.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_D5dKoDqQ2v7QNXhW1F8zF0ZKijovEPgp
#define BREEZE_GUARD_D5dKoDqQ2v7QNXhW1F8zF0ZKijovEPgp

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//      population_count():
//      ===================
//
//!\brief
//!     Returns the number of on bits in the binary representation of
//!     the value of `t`.
//!
//!     `T` must be an unsigned integral type.
//!
//!     \warning
//!         [FUTURE] This function template will be removed in favor of
//!         `std::popcount()` when Breeze will require C++20.
// ---------------------------------------------------------------------------
template< typename T >
constexpr int       population_count( T t ) noexcept ;

}

#include "brz/population_count.tpp"
#endif
