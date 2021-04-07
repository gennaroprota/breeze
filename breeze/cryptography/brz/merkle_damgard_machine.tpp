// ===========================================================================
//                     Copyright 2006-2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/cryptography/hashing_count.hpp"
#include "breeze/diagnostics/assert.hpp"
#include "breeze/endianness/endian_codec.hpp"
#include "breeze/iteration/begin_end.hpp"

#include <algorithm>

namespace breeze_ns {

template< typename Engine >
merkle_damgard_machine< Engine >::merkle_damgard_machine()
{
    reset() ;
}

template< typename Engine >
template< typename InputIter >
merkle_damgard_machine< Engine >::merkle_damgard_machine( InputIter begin,
                                                          InputIter end )
// [FUTURE], [C++11] [gps] this will forward to the default ctor
{
    reset() ;
    append( begin, end ) ;
}

template< typename Engine >
void
merkle_damgard_machine< Engine>::append( byte_type b )
{
    int const           index = input_index() ;
    m_input_buffer[ index ] = b ;
    update_count( byte_width ) ;

    if ( index == ( block_length - 1 ) ) {
        compress() ;
    }
}

template< typename Engine >
int
merkle_damgard_machine< Engine >::input_index() const
{
    return ( m_bit_count[ 0 ] / byte_width ) % block_length ;
}

template< typename Engine >
void
merkle_damgard_machine< Engine >::compress()
{
    //      Decode the input buffer to a buffer of words, according
    //      to the algorithm endianness, then forward the actual work
    //      to the engine.
    // -----------------------------------------------------------------------
    int const           sz = block_length / word_length ;
    word_type           input_in_words[ sz ] ;

    for ( int i = 0 ; i < sz ; ++ i ) {
        input_in_words[ i ] = Engine::decode_word(
                       breeze::begin( m_input_buffer ) + i * word_length ) ;
    }

    Engine::process_block( input_in_words, m_state ) ;
}

template< typename Engine >
void
merkle_damgard_machine< Engine >::reset()
{
    Engine::init_state( m_state ) ;

    std::fill( breeze::begin( m_bit_count ), breeze::end( m_bit_count ), 0 ) ;
    std::fill( breeze::begin( m_input_buffer ), breeze::end( m_input_buffer ),
        byte_type( 0 ) ) ;
}

template< typename Engine >
template< typename InputIter >
void
merkle_damgard_machine< Engine >::do_append( InputIter begin,
                                             InputIter end,
                                             std::input_iterator_tag )
{
    for ( ; begin != end ; ++ begin ) {
        append( *begin ) ; // gps value type=
    }
}

template< typename Engine >
template< typename RandomIter >
void
merkle_damgard_machine< Engine >::do_append( RandomIter begin,
                                             RandomIter end,
                                     std::random_access_iterator_tag )
{
    typedef typename std::iterator_traits< RandomIter >::difference_type
                        difference_type ;

    // bufferize/compress as many times as possible
    int                 index = input_index() ;
    RandomIter          curr( begin ) ;

    for ( difference_type avail( block_length - index ) ;
         (end - curr) >= avail ; curr += avail, avail = block_length ) {

        std::copy( curr, curr + avail,
            breeze::begin( m_input_buffer ) + index ) ;
        compress() ;
        index = 0 ;
    }

    // bufferize any remaining input; update the bit count
    std::copy( curr, end, breeze::begin( m_input_buffer ) + index ) ;
    update_count( byte_width * static_cast< long long >( end - begin ) ) ;
}

template< typename Engine >
template< typename Iter >
void
merkle_damgard_machine< Engine >::append( Iter begin, Iter end )
{
    typedef typename std::iterator_traits<
                        Iter >::iterator_category cat ;

    do_append( begin, end, cat() ) ;
}

//      Padding:
//
//      append a single 1 bit, always; then append as few (possibly
//      zero) 0 bits as needed to get a message whose last block has
//      room exactly for length_count words (that's the room to store
//      the bit-length of the unpadded message).
//
//      In all, at least one bit and at most an entire block is
//      appended.
//
// NOTE: the padding method described above is by far the most
//       commonly used; in principle, there could be variations
//       on this scheme, but no hash function that I know of uses
//       them. [gps]
//
// NOTE2: I'm not convinced this interface is good for security.
//        Perhaps we should force the user to take the digest?
// ---------------------------------------------------------------------------
template< typename Engine >
void
merkle_damgard_machine< Engine >::finalize()
{
    // room to append bit-length
    int const           r = word_length * length_count ;

    int const           filled = input_index() ;
    int const           avail = block_length - filled ;
    int const           pad_len = avail > r
                                    ? avail - r
                                    : block_length - r + avail ;

    byte_type           final_bytes[ block_length + r ] = {
        byte_type( 1 ) << ( byte_width - 1 ) } ;

    Engine::encode_length( m_bit_count, final_bytes + pad_len ) ;

    append( breeze::cbegin( final_bytes ),
            breeze::cbegin( final_bytes ) + pad_len + r ) ;
}

template< typename Engine >
void
merkle_damgard_machine< Engine >::create_digest( raw_digest_type & raw )
{
    finalize() ;

    //      We used to encode directly into `raw`, here. But this had to
    //      be changed for SHA-512/224:
    //
    //      SHA-512/224 uses 64-bit words but a digest of 224 bits. And
    //      224 is not a multiple of 64. So, we use a slightly larger
    //      intermediate buffer (64 * 4 = 256 bits), then copy only 224
    //      / 8 = 28 bytes from there into `raw`. To put it differently:
    //      since `raw` would have room for 3.5 words only, we encode 4
    //      of them into a temporary buffer, then only take 3.5 of them.
    //
    //      Note that SHA-224 doesn't cause this problem, because it
    //      uses 32-bit words, and 224 is a multiple of 32.
    // -----------------------------------------------------------------------
    int const           number_of_words_to_copy =
        digest_width % word_width == 0
            ? digest_width / word_width
            : digest_width / word_width + 1 ;

    byte_type           buffer[ word_length * number_of_words_to_copy ] ;
    for ( int i = 0 ; i < number_of_words_to_copy ; ++ i ) {
        Engine::encode_word( m_state[ i ],
                             buffer + i * word_length ) ;
    }

    std::copy_n( breeze::cbegin( buffer ),
                 digest_width / byte_width,
                 breeze::begin( raw ) ) ;
}

template< typename Engine >
void
merkle_damgard_machine< Engine >::update_count( long long amount )
{
    BREEZE_ASSERT( amount >= 0 ) ;

    typedef endian_codec< little_endian_policy,
                          unsigned long long,
                          length_unit_type
                      > codec ;

    static_assert( codec::required_count <= length_count, "" ) ;

    //      Encode a base-n representation of amount (n=2**32, 2**64,
    //      etc.); note that we *need* to zero out repr[], as it is
    //      typically larger than the type of the amount parameter.
    // -----------------------------------------------------------------------
    length_unit_type    repr[ length_count ] = {} ;
    codec::encode( amount, breeze::begin( repr ) ) ;

    int                 carry = 0 ;
    for ( int i = 0 ; i < length_count ; ++ i ) {
        length_unit_type const
                            w( m_bit_count[ i ] + repr[ i ] + carry ) ;
        carry = w < repr[ i ]
                    ? 1
                    : 0
                    ;
        m_bit_count[ i ] = w ;
    }

    //      A carry here means that the input message was longer than
    //      we can represent; now, either the specific hashing
    //      algorithm prescribes wrapping (MD5, for instance, does so)
    //      or we have to give up: in the latter case
    //      on_length_exhausted() will throw an exception. With numbers
    //      such as 2**64 and bigger, this is of course a very
    //      unlikely case.
    // -----------------------------------------------------------------------
    if ( carry != 0 ) {
        hashing_count::on_length_exhausted( Engine::count_mode ) ;
    }
}

}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
