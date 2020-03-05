// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include <functional>

namespace breath {

template< typename T >
constexpr T const &
clamp( T const & value, T const & low, T const & high )
{
    return clamp( value, low, high, std::less<>() ) ;
}

template< typename T, typename Compare >
constexpr T const &
clamp( T const & value,
       T const & low,
       T const & high,
       Compare comp )
{
    //      NOTE:
    //          no BREATH_ASSERT( ! comp( high, low ) ) here to avoid
    //          altering the stated complexity of the function (at most
    //          two applications of comp).
    // -----------------------------------------------------------------------
    return comp( value, low )
            ? low
            : comp( high, value )
                ? high
                : value
            ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
