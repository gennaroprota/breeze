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

#include "breath/cryptography/sha512_hasher.hpp"
#include "breath/cryptography/private/sensitive_buffer.hpp"
#include "breath/cryptography/private/sha_common.tpp"
#include "breath/iteration/begin_end.hpp"

#include <algorithm>
#include <functional>

namespace breath {
namespace        {

typedef sha512_engine::word_type
                    word_type ;
using sha_common_private::ror ;

word_type const     k[] =
{
    //      These words represent the first sixty-four bits of the
    //      fractional parts of the cube roots of the first eighty prime
    //      numbers.
    // -----------------------------------------------------------------------
    0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL,
    0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL,
    0x3956c25bf348b538ULL, 0x59f111f1b605d019ULL,
    0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL,
    0xd807aa98a3030242ULL, 0x12835b0145706fbeULL,
    0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL,
    0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL,
    0x9bdc06a725c71235ULL, 0xc19bf174cf692694ULL,
    0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL,
    0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL,
    0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL,
    0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL,
    0x983e5152ee66dfabULL, 0xa831c66d2db43210ULL,
    0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL,
    0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL,
    0x06ca6351e003826fULL, 0x142929670a0e6e70ULL,
    0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL,
    0x4d2c6dfc5ac42aedULL, 0x53380d139d95b3dfULL,
    0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL,
    0x81c2c92e47edaee6ULL, 0x92722c851482353bULL,
    0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL,
    0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL,
    0xd192e819d6ef5218ULL, 0xd69906245565a910ULL,
    0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL,
    0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL,
    0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL,
    0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL,
    0x5b9cca4f7763e373ULL, 0x682e6ff3d6b2b8a3ULL,
    0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL,
    0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL,
    0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL,
    0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL,
    0xca273eceea26619cULL, 0xd186b8c721c0c207ULL,
    0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL,
    0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL,
    0x113f9804bef90daeULL, 0x1b710b35131c471bULL,
    0x28db77f523047d84ULL, 0x32caab7b40c72493ULL,
    0x3c9ebe0a15c9bebcULL, 0x431d67c49c100d4cULL,
    0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL,
    0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL
} ;

word_type
big_sigma0( word_type x )
{
    return ror< 28 >( x ) ^ ror< 34 >( x ) ^ ror< 39 >( x ) ;
}

word_type
big_sigma1( word_type x )
{
    return ror< 14 >( x ) ^ ror< 18 >( x ) ^ ror< 41 >( x ) ;
}

word_type
sigma0( word_type x )
{
    return ror< 1 >( x ) ^ ror< 8 >( x ) ^ ( x >> 7 ) ;
}

word_type
sigma1( word_type x )
{
    return ror< 19 >( x ) ^ ror< 61 >( x ) ^ ( x >> 6 ) ;
}

}

void
sha512_engine::init_state( state_type & state )
{
    //      These words are obtained by taking the first sixty-four bits
    //      of the fractional parts of the square roots of the first
    //      eight prime numbers.
    // -----------------------------------------------------------------------
    state[ 0 ] = 0x6a09e667f3bcc908ULL ;
    state[ 1 ] = 0xbb67ae8584caa73bULL ;
    state[ 2 ] = 0x3c6ef372fe94f82bULL ;
    state[ 3 ] = 0xa54ff53a5f1d36f1ULL ;
    state[ 4 ] = 0x510e527fade682d1ULL ;
    state[ 5 ] = 0x9b05688c2b3e6c1fULL ;
    state[ 6 ] = 0x1f83d9abfb41bd6bULL ;
    state[ 7 ] = 0x5be0cd19137e2179ULL ;
}

void
sha512_engine::process_block( state_type & state, block_type const & block )
{
    using sha_common_private::ch ;
    using sha_common_private::maj ;

    //      Create an 80-word "schedule" from the message block.
    // -----------------------------------------------------------------------
    typedef word_type   schedule_type[ 80 ] ;
    sensitive_buffer< schedule_type >
                        sched(
                            breath::cbegin( block ), breath::cend( block ) ) ;
    for ( int i = 16 ; i < 80 ; ++ i ) {
        sched[ i ] = sigma1( sched[ i -  2 ] ) + sched[ i -  7 ]
                   + sigma0( sched[ i - 15 ] ) + sched[ i - 16 ] ;
    }
    sensitive_buffer< word_type[ 8 ] > working( state ) ;

    //      0 1 2 3 4 5 6 7
    //      a b c d e f g h
    // -----------------------------------------------------------------------
    {
        sensitive_buffer< word_type [ 2 ] >
                            t ;
        for ( int i = 0 ; i < 80 ; ++ i ) {

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
