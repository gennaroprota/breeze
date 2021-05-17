// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/diagnostics/assert.hpp"
#include "breeze/mathematics/gcd.hpp"
#include "breeze/mathematics/private/gcd_lcm_common.hpp"
#include <limits>
#include <type_traits>

namespace breeze_ns {

template< typename T >
constexpr T
lcm( T a, T b )
{
    static_assert( std::is_integral< T >::value, "T must be integral" ) ;

    using gcd_lcm_private::absolute_value ;

    T                   result = 0 ;

    if ( a != 0 && b != 0 ) {
        auto const          factor1 =
            absolute_value( a ) / breeze::gcd( a, b ) ;
        auto const          factor2 = absolute_value( b ) ;

        //      We renounce to using BREEZE_PREVENT_MACRO_EXPANSION
        //      here, for readability.
        // -------------------------------------------------------------------
        BREEZE_ASSERT( factor1 <=
                ( ( std::numeric_limits< T >::max )() / factor2 ) ) ;

        result = factor1 * factor2 ;
    }

    return result ;
}

}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
