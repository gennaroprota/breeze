// ===========================================================================
//                        Copyright 2021 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/diagnostics/assert.hpp"
#include "breeze/meta/constant.hpp"
#include "breeze/meta/has_sign.hpp"
#include "breeze/preprocessing/prevent_macro_expansion.hpp"
#include <limits>

namespace breeze_ns {
namespace checked_cast_private {

template< typename To, typename From >
class checker
{
    static constexpr To
    highest()
    {
        return std::numeric_limits< To >::max
            BREEZE_PREVENT_MACRO_EXPANSION () ;
    }

public:
    using               with_sign =    constant< bool, true > ;
    using               without_sign = constant< bool, false > ;

    static constexpr bool
    is_ok( From from, with_sign, with_sign )
    {
        return std::numeric_limits< To >::lowest() <= from
            && from <= highest() ;
    }

    static constexpr bool
    is_ok( From from, without_sign, without_sign )
    {
        return from <= highest() ;
    }

#   pragma warning( push )
#   pragma warning( disable: 4018 )
#   pragma warning( disable: 4388 )

#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wsign-compare"

    static constexpr bool
    is_ok( From from, with_sign, without_sign )
    {
        return from <= highest() ;
    }

    static constexpr void
    is_ok( From from, without_sign, with_sign )
    {
        return 0 <= from && from <= highest() ;
    }

#   pragma GCC diagnostic pop
#   pragma warning( pop )
} ;

}

template< typename To, typename From >
constexpr To
checked_cast( From from )
{
    static_assert( std::numeric_limits< To   >::is_specialized, "" ) ;
    static_assert( std::numeric_limits< From >::is_specialized, "" ) ;

    bool const          is_ok =
        checked_cast_private::checker< To, From >::
            is_ok( from, has_sign< To >(), has_sign< From >() ) ;
    BREEZE_ASSERT( is_ok ) ;

    return static_cast< To >( from ) ;
}

}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
