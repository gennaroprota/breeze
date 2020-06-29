// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/diagnostics/assert.hpp"
#include "breath/mathematics/is_power_of_2.hpp"
#include <limits>

namespace breath {
namespace integer_log2_private {

//      This constant is 4 because it must be a power of two less than
//      the width of uintmax_t. Since the minimum width for an
//      unsigned type (width of unsigned char) is 8, we start from 4.
//      We could actually start from 32, because uintmax_t must have
//      at least 64 value bits.
// ---------------------------------------------------------------------------
constexpr int       start_at = 4 ;

constexpr int
max_power_of_2_less_than_p( int p, int n = start_at ) noexcept
{
    BREATH_ASSERT( breath::is_power_of_2( static_cast< unsigned >( n ) ) ) ;

    return 2*n < p
        ? max_power_of_2_less_than_p( p, 2*n )
        : n
        ;
}

constexpr int
integer_log2_implementation( std::intmax_t x, int n ) noexcept
{
    int                 result = 0 ;
    while ( x !=  1 ) {
        std::intmax_t const
                            t = x >> n ;
        if ( t != 0 ) {
            result += n ;
            x = t ;
        }
        n /= 2 ;
    }
    return result ;
}

}

constexpr int
integer_log2( std::intmax_t x ) noexcept
{
    BREATH_ASSERT( x > 0 ) ;

    using namespace integer_log2_private ;

    constexpr int       n = max_power_of_2_less_than_p(
            std::numeric_limits< std::intmax_t >::digits
        ) ;
    return integer_log2_implementation( x, n ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
