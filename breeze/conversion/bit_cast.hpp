// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief An approximation of C++20's `std::bit_cast()`.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_zEfMFJHYQ9I08K6Rq2gIVv3NRdCzUKoU
#define BREEZE_GUARD_zEfMFJHYQ9I08K6Rq2gIVv3NRdCzUKoU

#include "breeze/top_level_namespace.hpp"
#include <type_traits>

namespace breeze_ns {

//      bit_cast():
//      ===========
//
//!\brief
//!     Copies an object representation.
//!
//!     Copies the object representation of the object referred to by
//!     `from` into an object `t` of type `std::remove_const_t< To >`
//!     and returns `t`.
//!
//!     This template participates in overload resolution only if `To`
//!     and `From` have the same size and are both <tt>
//!     TriviallyCopyable</tt>.
//!
//!     It is is an approximation of C++20's `std::bit_cast()`, for
//!     usage with C++14 and C++17.
//!
//!     The differences from the standard version are:
//!
//!      - it is not `constexpr` (allowing usage in a `constexpr`
//!        context would require compiler magic)
//!
//!      - requires that `To` be <tt>DefaultConstructible</tt>
//!
//!      - it is `noexcept( noexcept( To() ) )` (the standard version is
//!        unconditionally `noexcept`)
// ---------------------------------------------------------------------------
template< typename To, typename From >
std::enable_if_t< sizeof( To ) == sizeof( From ) &&
                  std::is_trivially_copyable< To   >::value &&
                  std::is_trivially_copyable< From >::value,
To >
bit_cast( From const & from ) noexcept( noexcept( To() ) ) ;

}

#include "brz/bit_cast.tpp"
#endif
