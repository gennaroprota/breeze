// ===========================================================================
//                     Copyright 2016-2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

namespace breeze_ns {

//      Implementation note:
//      ====================
//
//      If T has no sign, the two arguments to && can be swapped, thus
//      requiring a single test for non-null non-powers-of-2. I gave up
//      doing this optimization because using SFINAE for these things is
//      awful; it will be perhaps worth doing when we''ll have Concepts.
// ---------------------------------------------------------------------------
template< typename T >
constexpr bool      is_power_of_2( T x ) noexcept
{
    return x > 0 && ( x & ( x-1 ) ) == 0 ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
