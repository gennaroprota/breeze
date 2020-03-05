// ===========================================================================
//                        Copyright 2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/diagnostics/assert.hpp"

namespace breath {

template< typename T >
constexpr T
digital_root( T n, int base ) noexcept
{
    BREATH_ASSERT( n >= 0 && base >= 2 ) ;

    //      You have to use at least C99 or at least C++11 for the
    //      remainder to be specified for n == 0; so we special case it
    //      for C++03 compatibility, in case someone wants to extract
    //      this code.
    // -----------------------------------------------------------------------
    return n == 0
             ? 0
             : 1 + ( n - 1 ) % ( base - 1 ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
