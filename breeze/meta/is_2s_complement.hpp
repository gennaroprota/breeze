// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Tells whether a type uses a two's complement
//!            representation.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_tWPolV5CdSeUDR2dhiin3jIbwnOhvgwW
#define BREEZE_GUARD_tWPolV5CdSeUDR2dhiin3jIbwnOhvgwW

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//      is_2s_complement():
//      ===================
//
//!     \copybrief is_2s_complement.hpp
//!
//!     If `T` is not an integral type or a cv-qualified version
//!     thereof, the program is ill-formed. Otherwise
//!     `is_2s_complement()` returns true if and only if the type `T`
//!     uses a two's complement representation.
//!
//!     \note
//!         Starting with C++20, two's complement is the only
//!         representation allowed by the standard.
// ---------------------------------------------------------------------------
template< typename T >
constexpr bool      is_2s_complement() noexcept ;

}

#include "brz/is_2s_complement.tpp"
#endif
