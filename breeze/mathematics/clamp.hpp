// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief An implementation of the `clamp()` templates introduced
//!            in C++17.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_iVIpJl3Xhjhnj23ACP0NU6ffWo7q8kd4
#define BREEZE_GUARD_iVIpJl3Xhjhnj23ACP0NU6ffWo7q8kd4

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//      clamp():
//      ========
//
//!     \copybrief clamp.hpp
//!
//!     \pre
//!          - `T` shall be <tt>LessThanComparable</tt>
//!          - `high` shall be no lower than `low`
//!
//!     \return
//!         `low` if `value` is less than `low`, `high` if `high` is
//!         less than `value`, otherwise `value`
//!
//!     \par Complexity
//!         One or two comparisons.
//!
//!     \par Remarks
//!          - Returns a reference to `value` when `value` is equivalent
//!            to one (or both) of the boundary arguments.
//!          - If <tt>NaN</tt> is avoided, `T` can be a floating-point
//!            type.
// ---------------------------------------------------------------------------
template< typename T >
constexpr T const & clamp( T const & value, T const & low, T const & high ) ;

//      clamp():
//      ========
//
//!     \copybrief clamp.hpp
//!
//!     \pre
//!         `comp( high, low ) == false`
//!
//!     \return
//!         `low` if `value` is less than `low`, `high` if `high` is
//!         less than `value`, otherwise `value`.
//!
//!     \par Complexity
//!         One or two comparisons.
//!
//!     \par Remarks
//!          - Returns a reference to `value` when `value` is equivalent
//!            to one (or both) of the boundary arguments.
//!          - If <tt>NaN</tt> is avoided, `T` can be a floating-point
//!            type.
// ---------------------------------------------------------------------------
template< typename T, typename Compare  >
constexpr T const & clamp( T const & value,
                           T const & low,
                           T const & high,
                           Compare comp ) ;

}

#include "brz/clamp.tpp"
#endif
