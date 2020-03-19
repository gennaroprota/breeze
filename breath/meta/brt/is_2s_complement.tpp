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
is_2s_complement() noexcept
{
    static_assert( std::is_integral< T >::value,
                   "T must be an integral type" ) ;

    //      Caution: arguably, the "natural" form to use here would be
    //
    //        ( min() + max() ) == -1 ;
    //
    //      but, for e.g. T = unsigned int, that would mean
    //
    //        ( min() + max() ) == T( -1 ) ;
    //
    //      i.e.
    //
    //        ( min() + max() ) == max() ;
    //
    //      which would yield a false positive.
    // -----------------------------------------------------------------------
    return ( std::numeric_limits< T >::min BREATH_PREVENT_MACRO_EXPANSION ()
             + std::numeric_limits< T >::max BREATH_PREVENT_MACRO_EXPANSION () )
        < 0 ;
}

}
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
