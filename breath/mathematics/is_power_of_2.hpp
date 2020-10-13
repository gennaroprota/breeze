// ===========================================================================
//                     Copyright 2016-2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Tells if an integer is a power of two.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_33316YlRoQ2LToi0iu44YByR2XFvlCOy
#define BREATH_GUARD_33316YlRoQ2LToi0iu44YByR2XFvlCOy

#include "breath/top_level_namespace.hpp"

namespace breath_ns {

//      is_power_of_2():
//      ================
//
//!     \return
//!         \c true if an only if \c x is a power of two.
//!
//!     \note
//!         C++20 has \c std::has_single_bit(), which can replace this
//!         one (but only works with unsigned types and, on most
//!         implementations, qualified versions thereof).
// ---------------------------------------------------------------------------
template< typename T >
constexpr bool      is_power_of_2( T x ) noexcept ;

}

#include "brt/is_power_of_2.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
