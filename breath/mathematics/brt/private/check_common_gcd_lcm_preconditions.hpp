// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#ifndef BREATH_GUARD_ywAsFEinN5XbOP8UpDuYwWj4b3LAnVX2
#define BREATH_GUARD_ywAsFEinN5XbOP8UpDuYwWj4b3LAnVX2

#include "breath/diagnostics/assert.hpp"
#include "breath/meta/is_twos_complement.hpp"
#include <type_traits>
#include <limits>

namespace breath {
namespace gcd_lcm_private {

//      Renouncing to have a separate .tpp file, since this is a
//      private component.
// ---------------------------------------------------------------------------
template< typename M, typename N >
constexpr void
check_common_gcd_lcm_preconditions( M a, N b )
{
    static_assert( std::is_integral< M >::value
                && std::is_integral< N >::value, "M and N must be integral" ) ;

    BREATH_ASSERT( ( ! meta::is_twos_complement< M >()
        || a != std::numeric_limits< M >::min BREATH_PREVENT_MACRO_EXPANSION () )
        &&         ( ! meta::is_twos_complement< N >()
        || b != std::numeric_limits< N >::min BREATH_PREVENT_MACRO_EXPANSION () ) ) ;

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