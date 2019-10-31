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

#include <limits>
#include <type_traits>

namespace breath {

//      is_power_of_2():
//      ================
//
//!     \return
//!         \c true if an only if \c x is a power of two.
//!
//!     \note
//!         C++20 will likely have an ispow2() that can replace this one:
//!
//!           <http://wg21.link/p0556r3> (current as of writing this);
//!
//!           <http://wg21.link/p0556>   (latest).
// ---------------------------------------------------------------------------
template< typename T >
constexpr typename std::enable_if< std::numeric_limits< T >::is_integer &&
                                   ! std::numeric_limits< T >::is_signed &&
              ! std::is_same< typename std::remove_cv< T >::type, bool >::value,
                                   bool >::type
                    is_power_of_2( T x ) noexcept ;

}

#include "brt/is_power_of_2.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
