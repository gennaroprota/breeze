// ===========================================================================
//                     Copyright 2016-2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

namespace breath_ns {

template< typename T >
constexpr typename std::enable_if< std::numeric_limits< T >::is_integer &&
                                   ! std::numeric_limits< T >::is_signed &&
              ! std::is_same< typename std::remove_cv< T >::type, bool >::value,
                                   bool >::type
                    is_power_of_2( T x ) noexcept
{
    return ( x & ( x-1 ) ) == 0 && x > 0 ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
