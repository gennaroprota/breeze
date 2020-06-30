// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "private/gcd_lcm_common.hpp"
#include "breath/diagnostics/assert.hpp"
#include "breath/mathematics/gcd.hpp"
#include <limits>

namespace breath_ns {

template< typename M, typename N >
constexpr std::common_type_t< M, N >
lcm( M a, N b ) noexcept
{
    using gcd_lcm_private::check_common_gcd_lcm_preconditions ;
    using gcd_lcm_private::absolute_value ;

    check_common_gcd_lcm_preconditions( a, b ) ;

    typedef std::common_type_t< M, N >
                        common_type ;

    common_type         result = 0 ;

    if ( a != 0 && b != 0 ) {
        auto const          factor1 = absolute_value( a ) / gcd( a, b ) ;
        auto const          factor2 = absolute_value( b ) ;

        //      We renounce to using BREATH_PREVENT_MACRO_EXPANSION
        //      here, for readability.
        // -------------------------------------------------------------------
        BREATH_ASSERT( factor1 <=
                ( ( std::numeric_limits< common_type >::max )() / factor2 ) ) ;

        result = factor1 * factor2 ;
    }

    return result ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
