// ===========================================================================
//                     Copyright 2006-2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief  A Merkle-Damgard machine.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_fZUJ99c94EAQyLGNzV2BUxw0nzawpWpw
#define BREATH_GUARD_fZUJ99c94EAQyLGNzV2BUxw0nzawpWpw

#include <cstddef>

namespace breath {

template< typename Hasher >
class               digest ;


//      merkle_damgard_machine:
//      =======================
//
//!     This template models a simple state machine for
//!     Merkle-Damgard's construction of unkeyed hash functions.
//!
//!     Many popular hash functions (including MD5 and all the SHA
//!     variants) follow this scheme and can thus be implemented
//!     easily by means of this class template.
//!
//!
//!     \c Engine, which is the algorithm-specific policy, must
//!     provide the two static member functions described below:
//!
//!      - init_state( state_type & state )
//!        \c state_type is either a built-in array or an
//!        array-like type which provides const and non-const
//!        operator [] functions; the machine guarantees that data
//!        stored in the \c state parameter are wiped automatically
//!        when \c init_state() returns to the caller (for obvious
//!        security reasons)
//!
//!      - process_block()
//
//
//!     \warning
//!         Hash algorithms depend on exact bit-patterns,
//!         thus the byte/char representation (e.g. ASCII
//!         vs. EBCDIC) of the input matters. You might need
//!         a conversion to a common format before hashing.
//!
//!     \warning
//!         The current interface only supports hashing messages
//!         whose length is a multiple of the \c byte_width.
//!         In the future, bit iterators could be integrated here
//!         if possible.
//          (Note that internally we already keep the *bit* count
//          of the input, not the byte count, so extending it
//          should be fairly straightforward - gps )
//
//!     \par A note about \c std::accumulate()
//!
//!         You can "accumulate" data into a %merkle_damgard_machine by
//!         doing e.g.:
//!
//!         <code>
//!             std::accumulate( begin, end, my_hasher, functor ) ;
//!         </code>
//!
//!         with \c functor having the following function-call operator:
//!
//!         <code>
//!             hasher &
//!             operator()( hasher & h, hasher::byte_type c )
//!             {
//!                 h.push_back( c ) ;
//!                 return h ;
//!             }
//!         </code>
//!
//!         That, however, might be slow, due to excessive copying of
//!         the hasher.
//!
//!         If that occurs to you, please drop me a mail, in which case
//!         I might add a copy assignment operator to
//!         %merkle_damgard_machine which does nothing for
//!         self-assignment. In the mean time, please use \c
//!         std::for_each(), noting in a comment that you are using a
//!         less specific algorithm for performance reasons.
// ---------------------------------------------------------------------------
template< typename Engine >
class merkle_damgard_machine
{
    //      These are basically the algorithm (<=> the Engine's)
    //      "traits".
    // -----------------------------------------------------------------------
public:
    enum
    {
        byte_width   = Engine::byte_width,
        word_width   = Engine::word_width,
        digest_width = Engine::digest_width
    } ;

private:
    enum
    {
        block_length = Engine::block_width / byte_width,
        state_length = Engine::state_width / byte_width,
        word_length  = word_width / byte_width,

        length_count = Engine::length_exp / word_width
    } ;

    typedef typename Engine::word_type
                        word_type ;
    typedef typename Engine::byte_type
                        byte_type ;

    typedef typename Engine::state_type
                        state_type ;// gps --possibly temp
    typedef typename Engine::block_type
                        block_type ;// gps see above

public:
    //!     \name Initialization.
    //!     \{
    // -----------------------------------------------------------------------
                        merkle_damgard_machine() ;

    //!     Constructs from an input range.
    // -----------------------------------------------------------------------
    template< typename InputIter >
                        merkle_damgard_machine( InputIter begin, InputIter end ) ;
    //!     \}

    //!     \name Operations: "appending" one or more bytes
    //!     \{
    // -----------------------------------------------------------------------
    void                push_back( byte_type b ) ;

    template< typename InputIter >
    merkle_damgard_machine &
                        append( InputIter begin, InputIter end ) ;
    //!     \}

private:
    friend class digest< merkle_damgard_machine > ;

    typedef word_type   length_unit_type ;
    typedef byte_type   raw_digest_type[ digest_width / byte_width ] ;

    // data
    // gps do we characterize the Engine by count or by state_type?
    state_type          m_state ;// gps word_type        m_state[ state_count ] ;
    length_unit_type    m_bit_count[ length_count ] ; // low-unit first
    byte_type           m_input_buffer[ block_length ] ;

    void                compress() ;
    void                finalize() ;
    void                reset() ;
    void                create_digest( raw_digest_type & ) ;

    int                 input_index() const ;
    void                increase_count( ptrdiff_t amount ) ;

    template< typename It >
    merkle_damgard_machine &
                        do_append( It begin, It end,
                            std::input_iterator_tag const * ) ;

    template< typename It >
    merkle_damgard_machine &
                        do_append( It begin, It end,
                            std::random_access_iterator_tag const * ) ;
} ;

}

#include "brt/merkle_damgard_machine.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
