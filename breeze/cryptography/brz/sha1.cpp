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

#include "breeze/cryptography/sha1.hpp"
#include "breeze/cryptography/private/sha_common.tpp"
#include "breeze/iteration/begin_end.hpp"

#include <algorithm>
#include <functional>


//      NOTE:
//          All references in the comments below are relative to FIPS
//          180-2 with Change Notice 1, as indicated in the user
//          documentation.
// ---------------------------------------------------------------------------

namespace breeze_ns {
namespace           {

typedef sha1_engine::word_type word_type ;

//      Constants: section 4.2.1
// ---------------------------------------------------------------------------
word_type const     k[] = { 0x5a827999, 0x6ed9eba1,
                            0x8f1bbcdc, 0xca62c1d6 } ;


word_type
parity( word_type x, word_type y, word_type z )
{
    return x ^ y ^ z ;
}

//      Note:
//          this is not a general rotate-left template: it assumes
//          (which always happens with MD5 and SHA-1), that
//          0 < amount < 32.
// ---------------------------------------------------------------------------
template< int amount >
word_type
rotate_left( word_type w )
{
    return ( w << amount ) | ( w >> ( sha1_engine::word_width - amount ) ) ;
}

}

void
sha1_engine::init_state( state_type & state )
{
    //      Reference: section 5.3.1
    // -----------------------------------------------------------------------
    state[ 0 ] = 0x67452301 ;
    state[ 1 ] = 0xefcdab89 ;
    state[ 2 ] = 0x98badcfe ;
    state[ 3 ] = 0x10325476 ;
    state[ 4 ] = 0xc3d2e1f0 ;
}

//
//      Block processing - reference: section 6.1.2
// ---------------------------------------------------------------------------
void
sha1_engine::process_block( block_type const & block, state_type & state )
{
    using sha_common_private::ch ;
    using sha_common_private::maj ;

    //      Expand the message block to an 80-word "schedule".
    // -----------------------------------------------------------------------
    int const           sz = 80 ;
    word_type           sched[ sz ] ;
    std::copy( breeze::cbegin( block ), breeze::cend( block ),
        breeze::begin( sched ) ) ;
    for ( int i = 16 ; i < sz ; ++ i ) {
        sched[ i ] =
            rotate_left< 1 >( sched[ i - 3  ] ^ sched[ i - 8  ]
                            ^ sched[ i - 14 ] ^ sched[ i - 16 ] ) ;
    }

    //      Letter mapping to ease review against the FIPS standard:
    //              a b c d e
    //          [   0 1 2 3 4   ]
    // -----------------------------------------------------------------------
    int const           state_count = 5 ;
    word_type           working[ state_count ] ;
    std::copy( breeze::cbegin( state ), breeze::cend( state ),
        breeze::begin( working ) ) ;

    //      NOTE: analogously to the MD5 case, we repeat this code four
    //      times; forming an array of pointers to ch, parity and maj
    //      prevents their calls to be inlined, with most compilers; but
    //      perhaps there are (non-macro-based) other beneficial
    //      solutions. ([FUTURE] [gps])
    // -----------------------------------------------------------------------
    word_type           t = 0 ;
    for ( int i = 0 ; i < 20 ; ++ i ) {
        t = rotate_left< 5 >( working[ 0 ] )
          + ch( working[ 1 ], working[ 2 ], working[ 3 ] )
          + working[ 4 ] + k[ 0 ] + sched[ i ] ;
        working[ 4 ] = working[ 3 ] ;
        working[ 3 ] = working[ 2 ] ;
        working[ 2 ] = rotate_left< 30 >( working[ 1 ] ) ;
        working[ 1 ] = working[ 0 ] ;
        working[ 0 ] = t ;
    }
    for ( int i = 20 ; i < 40 ; ++ i ) {
        t = rotate_left< 5 >( working[ 0 ] )
          + parity( working[ 1 ], working[ 2 ], working[ 3 ] )
          + working[ 4 ] + k[ 1 ] + sched[ i ] ;
        working[ 4 ] = working[ 3 ] ;
        working[ 3 ] = working[ 2 ] ;
        working[ 2 ] = rotate_left< 30 >( working[ 1 ] ) ;
        working[ 1 ] = working[ 0 ] ;
        working[ 0 ] = t ;
    }
    for ( int i = 40 ; i < 60 ; ++ i ) {
        t = rotate_left< 5 >( working[ 0 ] )
          + maj( working[ 1 ], working[ 2 ], working[ 3 ] )
          + working[ 4 ] + k[ 2 ] + sched[ i ] ;
        working[ 4 ] = working[ 3 ] ;
        working[ 3 ] = working[ 2 ] ;
        working[ 2 ] = rotate_left< 30 >( working[ 1 ] ) ;
        working[ 1 ] = working[ 0 ] ;
        working[ 0 ] = t ;
    }
    for ( int i = 60 ; i < 80 ; ++ i ) {
        t = rotate_left< 5 >( working[ 0 ] )
          + parity( working[ 1 ], working[ 2 ], working[ 3 ] )
          + working[ 4 ] + k[ 3 ] + sched[ i ] ;
        working[ 4 ] = working[ 3 ] ;
        working[ 3 ] = working[ 2 ] ;
        working[ 2 ] = rotate_left< 30 >( working[ 1 ] ) ;
        working[ 1 ] = working[ 0 ] ;
        working[ 0 ] = t ;
    }

    std::transform( breeze::cbegin( state ), breeze::cend( state ),
                    breeze::cbegin( working ), breeze::begin( state ),
                    std::plus< word_type >() ) ;
}

}
