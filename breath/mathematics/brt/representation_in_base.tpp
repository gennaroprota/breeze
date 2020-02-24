// ===========================================================================
//                     Copyright 2018-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/diagnostics/assert.hpp"
#include "breath/counting/count.hpp"
#include <algorithm>
#include <cstddef>
#include <string>

namespace breath {

template< typename T >
std::string
representation_in_base( T n, int base )
{
    static char const   digits[] = "0123456789"
                                   "abcdefghijklmnopqrstuvwxyz" ;

    std::size_t const   max_base = breath::count( digits ) - 1 ;

    static_assert( max_base == 36, "" ) ;

    BREATH_ASSERT( n >= 0 ) ;
    BREATH_ASSERT( 2 <= base &&
        static_cast< std::size_t >( base ) <= max_base ) ;

    std::string         result ;

    do {
        result.push_back( digits[ n % base ] ) ;
        n /= base ;
    } while ( n != 0 ) ;

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
