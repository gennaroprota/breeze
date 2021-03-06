// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2011-2013 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/random/max_for_subrange.hpp"
#include "breeze/diagnostics/assert.hpp"

namespace breeze_ns {

//      Implementation notes:
//      ---------------------
//
//      We want to have a range [0, p] such that p + 1 (the number of
//      integer values that it contains) is a multiple of x + 1 (the
//      number of integer values in [0, x]).
//
//      Mathematically:
//
//         m + 1 = q(x + 1) + r
//
//      but *programmatically* we can't do that directly, because m + 1
//      may overflow. However, subtracting x + 1 from both members
//
//         m - x = (q - 1)(x + 1) + r
//
//      which says that we can obtain the same remainder r by performing
//      a division of m - x (which is non-negative) by x + 1.
//
//      And we can avoid overflow for x + 1, too, by simply treating the
//      case x == m separately.
//
//      Hence the implementation below.
// ---------------------------------------------------------------------------
long
max_for_subrange( long x, long m )
{
    BREEZE_ASSERT( x >= 0 ) ;
    BREEZE_ASSERT( x <= m ) ;

    //      Note how x + 1 cannot overflow in its branch (because,
    //      there, x < m, and m has the same type as x).
    // -----------------------------------------------------------------------
    return x == m
        ? m
        : m - ( (m-x) % (x+1) )
        ;
}

}
