// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/diagnostics/assert.hpp"

namespace breath {

template< typename Integer >
constexpr Integer
rounded_up_quotient( Integer a, Integer b ) noexcept
{
    BREATH_ASSERT( b != 0 ) ;

    //      We avoid introducing intermediate variables here, to make
    //      make this compilable with VC++ 2015. (TODO)
    // -----------------------------------------------------------------------
    return ( ( a > 0 && b > 0 ) || ( a < 0 && b < 0 ) ) && a % b != 0
                   ? a / b + 1
                   : a / b
                   ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
