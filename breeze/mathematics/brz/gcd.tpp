// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/mathematics/private/gcd_lcm_common.hpp"
#include "breeze/mathematics/private/would_division_overflow.hpp"
#include <type_traits>

namespace breeze_ns {

template< typename T >
constexpr T
gcd( T a, T b )
{
    static_assert( std::is_integral< T >::value, "T must be integral" ) ;
    using gcd_lcm_private::absolute_value ;
    using mathematics_private::would_division_overflow ;

    if ( would_division_overflow( b, a ) ||
            would_division_overflow( a, b ) ) {
        return 1 ;
    }

    while ( true ) {

        if ( a == 0 ) {
            return absolute_value( b ) ;
        }
        b %= a ;

        if ( b == 0 ) {
            return absolute_value( a ) ;
        }
        a %= b ;
    }
}

}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
