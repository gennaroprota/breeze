// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief The integer part of the logarithm, to base 2, of its
//!            argument.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_Kym3FA1ex9fw5x3d1rVgY686BX4YRKvw
#define BREEZE_GUARD_Kym3FA1ex9fw5x3d1rVgY686BX4YRKvw

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//      integer_log2():
//      ===============
//
//!\brief
//!     Returns the integer part of the logarithm, to base 2, of its
//!     argument.
//!
//!     \par Type requirements
//!         `T` must be an integral type other than `bool`.
//!
//!     \pre
//!         x > 0
// ---------------------------------------------------------------------------
template< typename T >
constexpr int       integer_log2( T x ) ;

}

#include "brz/integer_log2.tpp"
#endif
