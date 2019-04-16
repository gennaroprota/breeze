// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/meta/integer_log2.hpp"
#include <limits>

//      The argument x must be a power of two. This then makes a
//      recursive check up to x==2 (included), where each step
//      verifies x, x + 1 and x - 1. IOWs, it checks "across" powers
//      of two.
//
//      The specialization for < 1, 0 > just terminates the recursion.
//
//      Of course this will be initially invoked with 2 ** (w - 1),
//      where w is the width of static_log2's argument type.
// ---------------------------------------------------------------------------
using breath::meta::integer_log2 ;

template< breath::meta::integer_log2_argument_type x,
          breath::meta::integer_log2_result_type   expected
        >
struct log2_checker
{
    static_assert( integer_log2< x     >::value == expected,     "" ) ;
    static_assert( integer_log2< x + 1 >::value == expected,     "" ) ;
    static_assert( integer_log2< x - 1 >::value == expected - 1, "" ) ;

    static int const dummy = log2_checker< x / 2, expected - 1 >::dummy ;
} ;

template<>
struct log2_checker< 1, 0 >
{
    static int const dummy = 0 ;
} ;


int
main()
{
    typedef breath::meta::integer_log2_argument_type
                        arg_type ;
    typedef breath::meta::integer_log2_result_type
                        result_type ;

    using               breath::meta::integer_log2 ;

    // check that the typedefs respect the contract
    //
    static_assert(    arg_type( -1 ) > 0, "" ) ;
    static_assert( result_type( -1 ) < 0, "" ) ;

    const result_type width = std::numeric_limits< arg_type >::digits ;

    // check the maximum allowed argument...
    //
    const arg_type maximum = arg_type( -1 ) ;
    static_assert( integer_log2< maximum >::value == width - 1, "" ) ;

    // ... then go with the recursive check
    //
    const arg_type recursion_start = maximum - ( maximum >> 1 ) ;
    const int dummy = log2_checker< recursion_start, width - 1 >::dummy ;

    static_cast< void >( dummy ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
