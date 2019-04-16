// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "private/check_common_gcd_lcm_preconditions.hpp"
#include "breath/mathematics/gcd.hpp"
#include <cmath>

namespace breath {

template< typename M, typename N >
constexpr std::common_type_t< M, N >
lcm( M a, N b ) noexcept
{
    gcd_lcm_private::check_common_gcd_lcm_preconditions( a, b ) ;
    std::common_type_t< M, N > const
                        g = gcd( a, b ) ;
    return g == 0
        ? 0
        : std::abs( a ) / g * std::abs( b ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
