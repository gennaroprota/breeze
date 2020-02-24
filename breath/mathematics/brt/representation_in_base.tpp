// ===========================================================================
//                     Copyright 2018-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/diagnostics/assert.hpp"
#include "breath/counting/count.hpp"
#include "breath/meta/is_twos_complement.hpp"
#include <algorithm>
#include <cstddef>
#include <limits>
#include <string>
#include <type_traits>

namespace breath {

template< typename T >
std::string
representation_in_base( T n, int base )
{
    static char const   digits[] = "0123456789"
                                   "abcdefghijklmnopqrstuvwxyz" ;

    std::size_t const   max_base = breath::count( digits ) - 1 ;

    static_assert( max_base == 36, "" ) ;

    typedef typename std::make_unsigned< T >::type
                        unsigned_type ;

    unsigned_type       abs =
        n < 0
        ? breath::meta::is_twos_complement< T >() &&
            n == ( std::numeric_limits< T >::min )()
                ? unsigned_type( -1 ) / 2 + 1
                : - n
        : n
        ;

    BREATH_ASSERT( 2 <= base &&
        static_cast< std::size_t >( base ) <= max_base ) ;

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
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
