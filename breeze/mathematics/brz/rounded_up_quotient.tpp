// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/diagnostics/assert.hpp"
#include "breeze/mathematics/private/would_division_overflow.hpp"

namespace breeze_ns {

template< typename Integer >
constexpr Integer
rounded_up_quotient( Integer a, Integer b )
{
    BREEZE_ASSERT( b != 0 ) ;
    BREEZE_ASSERT( ! mathematics_private::would_division_overflow( a, b ) ) ;

    //      We avoid introducing intermediate variables here, to make
    //      this compilable with VC++ 2015. (TODO)
    // -----------------------------------------------------------------------
    return ( ( a > 0 && b > 0 ) || ( a < 0 && b < 0 ) ) && a % b != 0
                   ? a / b + 1
                   : a / b
                   ;
}

}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
