// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2006-2007 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/cryptography/sha256_hasher.hpp"
#include "breath/cryptography/private/sensitive_buffer.hpp"
#include "breath/cryptography/private/sha_common.tpp"
#include "breath/iteration/begin_end.hpp"

#include <algorithm>
#include <functional>

namespace breath {
namespace        {

typedef sha256_engine::word_type
                    word_type ;

using sha_common_private::ror ;

static word_type const
                    k[] =
{
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
} ;

word_type
sigma0( word_type x )
{
    return ror< 7 >( x ) ^ ror< 18 >( x ) ^ ( x >> 3 ) ;
}

word_type
sigma1( word_type x )
{
    return ror< 17 >( x ) ^ ror< 19 >( x ) ^ ( x >> 10 ) ;
}

word_type
big_sigma0( word_type x )
{
    return ror< 2 >( x ) ^ ror< 13 >( x ) ^ ror< 22 >( x ) ;
}

word_type
big_sigma1( word_type x )
{
    return ror< 6 >( x ) ^ ror< 11 >( x ) ^ ror< 25 >( x ) ;
}

}


void sha256_engine::init_state( state_type & state )
{
    // These values are obtained by taking the first 32 bits of the
    // fractional parts of the square roots of the first 8 prime numbers.

    state[ 0 ] = 0x6a09e667 ;
    state[ 1 ] = 0xbb67ae85 ;
    state[ 2 ] = 0x3c6ef372 ;
    state[ 3 ] = 0xa54ff53a ;
    state[ 4 ] = 0x510e527f ;
    state[ 5 ] = 0x9b05688c ;
    state[ 6 ] = 0x1f83d9ab ;
    state[ 7 ] = 0x5be0cd19 ;
}

void sha256_engine::process_block( state_type & state,
                                   block_type const & block )
{
    using sha_common_private::ch ;
    using sha_common_private::maj ;

    // expand the message-block to a 64-word "schedule"
    int const           sz( 64 ) ;
    typedef word_type   schedule_type[ sz ] ;
    sensitive_buffer< schedule_type >
                        sched(
                            breath::cbegin( block ), breath::cend( block ) ) ;
    for ( int i = 16 ; i < sz ; ++ i ) {
        sched[ i ] = sigma1( sched[ i - 2  ] ) + sched[ i - 7  ]
                   + sigma0( sched[ i - 15 ] ) + sched[ i - 16 ] ;
    }
   // 0 1 2 3 4 5 6 7
   // a b c d e f g h
   //
   int const            state_count( 8 ) ;
   sensitive_buffer< word_type[ state_count ] >
                        working( state ) ;
   {
       sensitive_buffer< word_type [ 2 ] >
                            t ;
       for ( int i = 0 ; i < 64 ; ++ i ) {

           t[ 0 ] = working[ 7 ] + big_sigma1( working[ 4 ] )
                  + ch( working[ 4 ], working[ 5 ], working[ 6 ] )
                  + k[ i ] + sched[ i ] ;
           t[ 1 ] = big_sigma0( working[ 0 ] )
                  + maj( working[ 0 ], working[ 1 ], working[ 2 ] ) ;

           working[ 7 ] = working[ 6 ] ;
           working[ 6 ] = working[ 5 ] ;
           working[ 5 ] = working[ 4 ] ;
           working[ 4 ] = working[ 3 ] + t[ 0 ] ;
           working[ 3 ] = working[ 2 ] ;
           working[ 2 ] = working[ 1 ] ;
           working[ 1 ] = working[ 0 ] ;
           working[ 0 ] = t[ 0 ] + t[ 1 ] ;
       }
   }

   std::transform( breath::cbegin( state ), breath::cend( state ),
                   breath::cbegin( working ), breath::begin( state ),
                   std::plus< word_type >() ) ;

}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
