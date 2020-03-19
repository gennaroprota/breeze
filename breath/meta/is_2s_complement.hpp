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

#ifndef BREATH_GUARD_tWPolV5CdSeUDR2dhiin3jIbwnOhvgwW
#define BREATH_GUARD_tWPolV5CdSeUDR2dhiin3jIbwnOhvgwW

namespace breath {
namespace meta {

//      is_2s_complement():
//      ===================
//
//!     If \c T is not an integral type or a cv-qualified version
//!     thereof, the program is ill-formed. Otherwise \c
//!     is_2s_complement() returns true if and only if the type \c T
//!     uses a two's complement representation.
//!
//!     \note
//!         Starting with C++20, two's complement is the only
//!         representation allowed by the standard.
// ---------------------------------------------------------------------------
template< typename T >
constexpr bool      is_2s_complement() noexcept ;

}
}

#include "brt/is_2s_complement.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
