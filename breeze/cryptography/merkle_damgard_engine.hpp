// ===========================================================================
//                     Copyright 2006-2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief  Base class template to ease the definition of policies
//!             for the \c merkle_damgard_machine template.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_fYqwSU8p6zoTOMzKlvSB4iz96M3PyUF5
#define BREEZE_GUARD_fYqwSU8p6zoTOMzKlvSB4iz96M3PyUF5

#include "breeze/top_level_namespace.hpp"
#include "breeze/cryptography/hashing_count.hpp"
#include "breeze/endianness/endian_codec.hpp"
#include "breeze/meta/integer_by_width.hpp"

#include <cstddef>

namespace breeze_ns {

//!     \copybrief merkle_damgard_engine.hpp
//
//!     All parameters here have pretty much self-explanatory names.
//!     The only exception is perhaps \c length_exponent: it determines
//!     the maximum message length that the engine will keep track of:
//!     attempting to digest a message of <tt>2**length_exponent</tt>
//!     bits or more either "wraps" or results in an exception, as
//!     established by the parameter \c count_type (in theory there's no
//!     guarantee that the maximum length, if any, is of the form <tt>
//!     2**e - 1</tt>, but that's what all one-way hash functions I know
//!     of do).
// ---------------------------------------------------------------------------
template< int                 bits_per_digest,
          int                 bits_per_block,
          typename            EndianPolicy,
          int                 bits_per_word   = 32,
          int                 bits_per_state  = bits_per_digest,
          hashing_count::type count_type = hashing_count::is_limited,
          int                 bits_per_byte   = 8,
          int                 length_exponent = 2 * bits_per_word
>
class merkle_damgard_engine
{
public:

    typedef typename unsigned_integer_by_width< bits_per_byte >::type
                        byte_type ;
    typedef typename unsigned_integer_by_width< bits_per_word >::type
                        word_type ;

    enum
    {
        digest_width = bits_per_digest,
        block_width  = bits_per_block,
        word_width   = bits_per_word,
        state_width  = bits_per_state,
        byte_width   = bits_per_byte,

        length_exp   = length_exponent
    } ;

    static hashing_count::type const
                        count_mode = count_type ;

    typedef word_type   state_type[ state_width / word_width ] ;
    typedef word_type   block_type[ block_width / word_width ] ;

private:
    enum { max_words =   ( length_exp / bits_per_word )
                     + ( ( length_exp % bits_per_word ) ? 1 : 0 ) } ;

    typedef endian_codec< EndianPolicy, word_type, byte_type >
                        word_codec ;

public:
    static void         encode_word( word_type w, byte_type * dest )
    {
        word_codec::encode( w, dest ) ;
    }

    static word_type    decode_word( byte_type const * src )
    {
        return word_codec::decode( src ) ;
    }

    //      This function implements the most common way used in a
    //      Merkle-Damgard construction to encode the message length at
    //      the end of the input message. Note that the length, in bits,
    //      is encoded into an array of *word_types*, even though the
    //      general hasher templates could in theory use a different
    //      type.
    // -----------------------------------------------------------------------
    static void encode_length( word_type const ( &len )[ max_words ],
                               byte_type * dest )
    {
        typedef word_type len_type[ max_words ] ;

        //      Note:
        //          a) len[ 0 ] is always the *least* significant word
        //          b) the order in which the words will "appear" in
        //             [dest, end), and the order of the bytes within
        //             each word, follow EndianPolicy
        // -------------------------------------------------------------------
        int const           step = word_width / byte_width ;
        for ( int i = 0 ; i < max_words ; ++ i ) {

            std::ptrdiff_t const
                            index =
                step * EndianPolicy::template index< len_type,
                                                     word_type >( i ) ;
            breeze::endian_store< EndianPolicy >(
                len[ max_words - 1 - i ], dest + index ) ;
        }
    }
} ;

template< int bits_per_digest,
        int bits_per_block,
        typename EndianPolicy,
        int bits_per_word,
        int bits_per_state,
        hashing_count::type count_type,
        int bits_per_byte,
        int length_exponent
>
hashing_count::type const
merkle_damgard_engine< bits_per_digest,
                       bits_per_block,
                       EndianPolicy,
                       bits_per_word,
                       bits_per_state,
                       count_type,
                       bits_per_byte,
                       length_exponent
    >::count_mode ;

}

#endif
