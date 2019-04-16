// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/preprocessing/prevent_macro_expansion.hpp"
#include <type_traits>
#include <limits>

namespace breath {
namespace meta {

template< typename T >
constexpr bool
is_twos_complement() noexcept
{
    static_assert( std::is_integral< T >::value, "T must be an integral type" ) ;

    return ( std::numeric_limits< T >::min BREATH_PREVENT_MACRO_EXPANSION ()
             + std::numeric_limits< T >::max BREATH_PREVENT_MACRO_EXPANSION() )
        == -1 ;
}

}
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
