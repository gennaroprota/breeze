// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/diagnostics/assert.hpp"
#include "breeze/mathematics/is_power_of_2.hpp"
#include <limits>
#include <type_traits>

namespace breeze_ns {
namespace integer_log2_private {

//      This constant is 4 because it must be a power of two less than
//      the width of T. Since the minimum width for an integral type
//      other than bool is 8, we start from 4.
// ---------------------------------------------------------------------------
constexpr int       start_at = 4 ;

constexpr int
max_power_of_2_less_than( int p, int n = start_at )
{
    BREEZE_ASSERT( breeze::is_power_of_2( static_cast< unsigned >( n ) ) ) ;

    return 2*n < p
        ? max_power_of_2_less_than( p, 2*n )
        : n
        ;
}

template< typename T >
constexpr int
integer_log2_implementation( T x, int n ) noexcept
{
    int                 result = 0 ;
    while ( x !=  1 ) {
        T const             t = x >> n ;
        if ( t != 0 ) {
            result += n ;
            x = t ;
        }
        n /= 2 ;
    }
    return result ;
}

}

template< typename T >
constexpr int
integer_log2( T x )
{
    static_assert( std::is_integral< T >::value, "" ) ;

    BREEZE_ASSERT( x > 0 ) ;

    using namespace integer_log2_private ;

    constexpr int       n = max_power_of_2_less_than(
            std::numeric_limits< T >::digits
        ) ;
    return integer_log2_implementation( x, n ) ;
}

}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
