// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief An implementation of the \c clamp() templates introduced
//!            in C++17.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_iVIpJl3Xhjhnj23ACP0NU6ffWo7q8kd4
#define BREATH_GUARD_iVIpJl3Xhjhnj23ACP0NU6ffWo7q8kd4

#include "breath/top_level_namespace.hpp"

namespace breath_ns {

//      clamp():
//      ========
//
//!     \copybrief clamp.hpp
//!
//!     \pre
//!      1. \c T shall be \c LessThanComparable
//!      2. \c high shall be no lower than \c low
//!
//!     \return
//!         \c low if \c value is less than \c low, \c high if \c
//!         value is higher than \c high, otherwise \c value
//!
//!     Complexity:
//!         One or two comparisons.
//!
//!     Remarks:
//!         Returns a reference to \c value when \c value is
//!         equivalent to one (or both) of the boundary arguments.
//!
//!         If <tt>NaN</tt> is avoided, \c T can be a floating-point
//!         type.
// ---------------------------------------------------------------------------
template< typename T >
constexpr T const & clamp( T const & value, T const & low, T const & high ) ;

//      clamp():
//      ========
//
//!     \copybrief clamp.hpp
//!
//!     \pre
//!         <code>comp( high, low ) == false</code>
//!
//!     \return
//!         \c low if \c value is less than \c low, \c high if \c
//!         value is higher than \c high, otherwise \c value.
//!
//!     Complexity:
//!         One or two comparisons.
//!
//!     Remarks:
//!         Returns a reference to \c value when \c value is
//!         equivalent to one (or both) of the boundary arguments.
//!
//!         If <tt>NaN</tt> is avoided, \c T can be a floating-point
//!         type.
// ---------------------------------------------------------------------------
template< typename T, typename Compare  >
constexpr T const & clamp( T const & value,
                           T const & low,
                           T const & high,
                           Compare comp ) ;

}

#include "brt/clamp.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
