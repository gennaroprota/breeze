// ===========================================================================
//                        Copyright 2007 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Arrays and containers element counter.
//!
//!     `signed_count()` provides an extension of `container::size()`
//!     that covers both standard containers and built-in arrays.
//!
//!     The syntax is, uniformly, `breeze::signed_count( a )` regardless
//!     of the actual type of `a`.
//!
//!     Following C++ best practices, these templates return a \e signed
//!     integer. They are made obsolete in C++20 by the namespace-scope
//!     `std::ssize()`'s. However our version avoids any fancy
//!     derivation of the return type, even for containers.
//!
//!     \see
//!         begin(), end(), cbegin(), cend().
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_ivBlyIgMoh0KJl1p5J44xFCWiI9nPqRi
#define BREEZE_GUARD_ivBlyIgMoh0KJl1p5J44xFCWiI9nPqRi

#include "breeze/top_level_namespace.hpp"
#include "breeze/conversion/checked_cast.hpp"
#include <climits>
#include <cstddef>

namespace breeze_ns {

//      signed_count():
//      ===============
//
//!     \copydoc signed_count.hpp
//!
//!     \return
//!         The number of elements of the array argument (obviously,
//!         `n`), cast to `long long`. The program is ill-formed if `n >
//!          LLONG_MAX`.
// ---------------------------------------------------------------------------
template< typename T, std::size_t n >
constexpr long long
signed_count( T const ( & )[ n ] ) noexcept
{
    static_assert( n <= LLONG_MAX, "" ) ;
    return static_cast< long long >( n ) ;
}

//      signed_count():
//      ===============
//
//!     \copydoc signed_count.hpp
//!
//!     \return
//!         breeze::checked_cast< long long >( t.size() ).
// ---------------------------------------------------------------------------
template< typename T >
constexpr long long
signed_count( T const & t )
{
    return breeze::checked_cast< long long >( t.size() ) ;
}

}

#endif
