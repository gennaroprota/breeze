// ===========================================================================
//                     Copyright 2006-2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/algorithm/secure_fill.hpp"
#include "breath/diagnostics/assert.hpp"
#include "breath/endianness/endian_codec.hpp"
#include "breath/iteration/begin_end.hpp"

#include <algorithm>
#include <iterator>

namespace breath {

//!     Support for \c breath::accumulate().
// ---------------------------------------------------------------------------
template< typename Engine >
class accumulate_traits< merkle_damgard_machine< Engine > >
{
    typedef merkle_damgard_machine< Engine >
                        machine_type ;

public:
    typedef machine_type
                        init_type ;
    typedef machine_type
                        result_type ;

    template< typename It >
    static result_type  compute( It begin, It end, init_type & v )
    {
        return v.append( begin, end ) ;
    }
} ;

// [FUTURE], [C++11]: template typedef (using) for
//           accumulator< Hasher, merkle_damgard_accumulation_policy >
// [gps]

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
merkle_damgard_machine< Engine>::push_back( byte_type b )
{
    int const           index( input_index() ) ;
    m_input_buffer[ index ] = b ;
    increase_count( byte_width ) ;

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
    //
    //      We always clear potentially sensitive data (i.e.:
    //      m_input_buffer and m_input_in_words).
    // -----------------------------------------------------------------------
    int const           sz = block_length / word_length ;
    word_type           input_in_words[ sz ] ;

    for ( int i = 0 ; i < sz ; ++ i ) {
        input_in_words[ i ] = Engine::decode_word(
                       breath::begin( m_input_buffer ) + i * word_length ) ;
    }

    // clear input data, for security
    breath::secure_fill( m_input_buffer ) ; // gps - improve idiom here

    Engine::process_block( m_state, input_in_words ) ;

    breath::secure_fill( input_in_words ) ;
}

// securely wipes all data (gps - at construction?)
template< typename Engine >
void
merkle_damgard_machine< Engine >::reset()
{
    Engine::init_state( m_state ) ;

    breath::secure_fill( m_bit_count ) ;
    breath::secure_fill( m_input_buffer ) ;
}

template< typename Engine >
template< typename InputIter >
merkle_damgard_machine< Engine > &
merkle_damgard_machine< Engine >::do_append( InputIter begin,
                                             InputIter end,
                                             std::input_iterator_tag const * )
{
    for ( ; begin != end ; ++ begin ) {
        push_back( *begin ) ; // gps value type=
    }

    return *this ;
}

template< typename Engine >
template< typename RandomIter >
merkle_damgard_machine< Engine > &
merkle_damgard_machine< Engine >::do_append( RandomIter begin,
                                             RandomIter end,
                                     std::random_access_iterator_tag const * )
{
    typedef typename std::iterator_traits< RandomIter >::difference_type
                        difference_type ;

    // bufferize/compress as many times as possible
    int                 index( input_index() ) ;
    RandomIter          curr( begin ) ;

    for ( difference_type avail( block_length - index ) ;
         (end - curr) >= avail ; curr += avail, avail = block_length ) {

        std::copy( curr, curr + avail,
            breath::begin( m_input_buffer ) + index ) ;
        compress() ;
        index = 0 ;
    }

    // bufferize any remaining input; update the bit count
    std::copy( curr, end, breath::begin( m_input_buffer ) + index ) ;
    increase_count( byte_width * ( end - begin ) ) ;

    return *this ;
}


template< typename Engine >
template< typename Iter >
merkle_damgard_machine< Engine > &
merkle_damgard_machine< Engine >::append( Iter begin, Iter end )
{
    typedef typename std::iterator_traits<
                        Iter >::iterator_category cat ;

    return do_append( begin, end, static_cast< cat * >( 0 ) ) ;
}

//      Padding:
//
//      append a single 1-bit, always; then append as few (possibly
//      zero) 0-bits as needed to get a message whose last block has
//      room exactly for length_count words (that's the room to store
//      the bitlength of the unpadded message).
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
    enum { r = word_length * length_count } ; // room to append bit-length

    // save a representation in bytes of the unpadded bit-length
    byte_type           message_len[ r ] ;
    Engine::encode_length( m_bit_count, breath::begin( message_len ) ) ;

    // append padding
    int const           filled( input_index() ) ;
    int const           pad_len(
            ( filled + r < block_length
              ? 1 : 2 ) * block_length - ( filled + r ) ) ;

    static byte_type const
                        padding[ block_length ] = { 0x80 } ;
    append( breath::cbegin( padding ), breath::cbegin( padding ) + pad_len ) ;

    // append byte-based representation of the unpadded bit-length
    append( breath::cbegin( message_len ), breath::cend( message_len ) ) ;
}

template< typename Engine >
void
merkle_damgard_machine< Engine >::create_digest( raw_digest_type & raw )
{
    finalize() ;
    for ( int i = 0 ; i < digest_width / word_width ; ++ i ) {
        Engine::encode_word( m_state[ i ],
                             raw + i * word_length ) ;
    }

    reset() ; // gps -- OK to reinitialize with the magic constants?
}

template< typename Engine >
void
merkle_damgard_machine< Engine >::increase_count( std::ptrdiff_t amount )
{
    BREATH_ASSERT( amount >= 0 ) ;

    typedef endian_codec< little_endian_policy,
                          std::size_t,
                          length_unit_type
                      > codec ;

    static_assert( codec::required_count <= length_count, "" ) ;

    //      Encode a base-n representation of amount (n=32, 64, etc.);
    //      note that we *need* to zero out repr[], as it is
    //      typically larger than the type of the amount parameter.
    // -----------------------------------------------------------------------
    length_unit_type    repr[ length_count ] = {} ;
    codec::encode( amount, breath::begin( repr ) ) ;

    int                 carry( 0 ) ;
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
    //      on_length_exhausted will throw an exception. With numbers
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
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
