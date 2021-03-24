// ===========================================================================
//                     Copyright 2018-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/diagnostics/assert.hpp"
#include "breeze/counting/signed_count.hpp"
#include "breeze/meta/is_2s_complement.hpp"
#include <algorithm>
#include <cstddef>
#include <limits>
#include <string>
#include <type_traits>

namespace breeze_ns {

template< typename T >
std::string
representation_in_base( T n, int base )
{
    static char const   digits[] = "0123456789"
                                   "abcdefghijklmnopqrstuvwxyz" ;

    long long const     max_base = breeze::signed_count( digits ) - 1 ;

    static_assert( max_base == 36, "" ) ;

    typedef typename std::make_unsigned< T >::type
                        unsigned_type ;

    unsigned_type       abs =
        n < 0
        ? breeze::meta::is_2s_complement< T >() &&
            n == ( std::numeric_limits< T >::min )()
                ? unsigned_type( -1 ) / 2 + 1
                : - n
        : n
        ;

    BREEZE_ASSERT( 2 <= base && base <= max_base ) ;

    std::string         result ;

    do {
        result.push_back( digits[ abs % base ] ) ;
        abs /= base ;
    } while ( abs != 0 ) ;

    if ( n < 0 ) {
        result.push_back( '-' ) ;
    }

    std::reverse( result.begin(), result.end() ) ;
    return result ;
}

}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
