// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/meta/has_sign.hpp"
#include "breeze/preprocessing/prevent_macro_expansion.hpp"
#include <limits>
#include <type_traits>

namespace breeze_ns {
namespace mathematics_private {

//      A reimplementation of our is_2s_complement() in terms of a class
//      template, because MSVC 2017 isn't able to handle the
//      breeze::meta version in the SFINAE context of
//      would_division_overflow(), below.
// ---------------------------------------------------------------------------
template< typename T >
class is_2s_complement
{
private:
    static T const      min = std::numeric_limits< T >::min
        BREEZE_PREVENT_MACRO_EXPANSION () ;

    static T const      max = std::numeric_limits< T >::max
        BREEZE_PREVENT_MACRO_EXPANSION () ;

public:
    static bool const   value = ( min + max ) < 0 ;
} ;

template< typename T >
constexpr std::enable_if_t<
    is_2s_complement< T >::value,
    bool >
would_division_overflow( T a, T b )
{
    T const             min = std::numeric_limits< T >::min
        BREEZE_PREVENT_MACRO_EXPANSION () ;

    return a == min && b == -1 ;
}

template< typename T >
constexpr std::enable_if_t<
    ! is_2s_complement< T >::value,
    bool >
would_division_overflow( T, T )
{
    return false ;
}

}
}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
