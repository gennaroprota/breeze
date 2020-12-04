// ===========================================================================
//                        Copyright 2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/diagnostics/assert.hpp"

namespace breeze_ns {

template< typename T >
constexpr int
digital_root( T n, int base )
{
    BREEZE_ASSERT( n >= 0 && base >= 2 ) ;

    return n == 0
             ? 0
             : 1 + ( n - 1 ) % ( base - 1 ) ;
}

}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
