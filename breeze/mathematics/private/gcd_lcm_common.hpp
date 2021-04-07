// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//      Renouncing to have a separate .tpp file, since these are private
//      components.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_ywAsFEinN5XbOP8UpDuYwWj4b3LAnVX2
#define BREEZE_GUARD_ywAsFEinN5XbOP8UpDuYwWj4b3LAnVX2

#include "breeze/top_level_namespace.hpp"
#include "breeze/meta/has_sign.hpp"
#include <type_traits>

namespace breeze_ns {
namespace gcd_lcm_private {

//      We use this because std::abs() is not required to be constexpr.
//
//      Note that the obvious implementation yields a C4146 from MSVC
//      2017 when T is unsigned (unary minus applied to unsigned), so we
//      take action and split the two cases...
// ---------------------------------------------------------------------------
template< typename T >
constexpr std::enable_if_t<
    has_sign< T >::value,
    T >
absolute_value( T x )
{
    return x < 0
               ? static_cast< T >( -x )
               : x
               ;
}

template< typename T >
constexpr std::enable_if_t<
    ! has_sign< T >::value,
    T >
absolute_value( T x )
{
    return x ;
}

}
}

#endif
