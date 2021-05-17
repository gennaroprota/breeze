// ===========================================================================
//                     Copyright 2016-2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include <limits>

namespace breeze_ns {

//      Implementation note:
//      ====================
//
//      If T has no sign, the two operands of && can be swapped, thus
//      requiring a single test for non-null non-powers-of-2. Since I
//      didn't do any measurement, and I wanted to keep things simple,
//      I'm not doing this.
// ---------------------------------------------------------------------------
template< typename T >
constexpr bool
is_power_of_2( T x ) noexcept
{
    static_assert( std::numeric_limits< T >::is_integer, "" ) ;

    return x > 0 && ( x & ( x - 1 ) ) == 0 ;
}

}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
