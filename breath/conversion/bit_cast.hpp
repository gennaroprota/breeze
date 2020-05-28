// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief An approximation of C++20's \c std::bit_cast().
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_zEfMFJHYQ9I08K6Rq2gIVv3NRdCzUKoU
#define BREATH_GUARD_zEfMFJHYQ9I08K6Rq2gIVv3NRdCzUKoU

#include <type_traits>

namespace breath {

//      bit_cast():
//      ===========
//
//!     Copies the object representation of the object referred to by \c
//!     from into an object \c t of type <code>std::remove_const_t< To >
//!     </code> and returns \c t.
//!
//!     This template participates in overload resolution only if \c To
//!     and \c From have the same size and are both \c
//!     TriviallyCopyable.
//!
//!     It is is an approximation of C++20's \c std::bit_cast(), for
//!     usage with C++14 and C++17.
//!
//!     The differences from the standard version are:
//!
//!      - it is not \c constexpr (allowing usage in a \c constexpr
//!        context would require compiler magic)
//!
//!      - requires that \c To be \c DefaultConstructible
//!
//!      - it is <code>noexcept( noexcept( To() ) )</code> (the standard
//!        version is unconditionally \c noexcept)
// ---------------------------------------------------------------------------
template< typename To, typename From >
std::enable_if_t< sizeof( To ) == sizeof( From ) &&
                  std::is_trivially_copyable< To   >::value &&
                  std::is_trivially_copyable< From >::value,
To >
bit_cast( From const & from ) noexcept( noexcept( To() ) ) ;

}

#include "brt/bit_cast.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
