// ===========================================================================
//                     Copyright 2006-2007 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief  SHA functions common code.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_YZVt6T2boY9RlFkqeiYohH0bEc6w6tsM
#define BREATH_GUARD_YZVt6T2boY9RlFkqeiYohH0bEc6w6tsM

#include "breath/top_level_namespace.hpp"
#include <limits>

namespace breath_ns {
namespace sha_common_private {

//      The "choice" function - for each bit position p it acts as a
//      conditional: "if x(p) then y(p) else z(p)".
// ---------------------------------------------------------------------------
template< typename T >
T
ch( T x, T y, T z )
{
    return ( x & y ) | ( ~x & z ) ;
}

//      "Majority" function - for each bit position the result is 1 if
//      and only if at least two of the three bits are 1.
// ---------------------------------------------------------------------------
template< typename T >
T
maj( T x, T y, T z )
{
    return ( x & y ) | ( x & z ) | ( y & z ) ;
}

//      Rotate right - usual constraints on amount apply.
// ---------------------------------------------------------------------------
template< int amount, typename T >
T
ror( T x )
{
    return ( x >> amount )
         | ( x << ( std::numeric_limits< T >::digits - amount ) ) ;
}

}
}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:

