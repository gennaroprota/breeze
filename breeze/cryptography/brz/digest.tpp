// ===========================================================================
//                     Copyright 2006-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/iteration/begin_end.hpp"
#include <algorithm>
#include <ostream>

//!     \todo Provide a way to extract from streams

namespace breeze_ns {

template< typename Hasher >
digest< Hasher >::digest( Hasher hasher_copy )
{
    // should the digest provide word-iterators?? -gps

    hasher_copy.create_digest( m_raw_digest ) ;
}

template< typename Hasher >
template< typename InputIter >
digest< Hasher >::digest( InputIter begin, InputIter end )
{
    Hasher              hasher( begin, end ) ;
    hasher.create_digest( m_raw_digest ) ;
}

template< typename Hasher >
bool
digest< Hasher >::is_equal( digest< Hasher > const & other ) const
{
    return std::equal( this->begin(), this->end(), other.begin() ) ;
}

template< typename Hasher >
typename digest< Hasher >::const_iterator
digest< Hasher >::begin() const
{
    return breeze::begin( m_raw_digest ) ;
}

template< typename Hasher >
typename digest< Hasher >::const_iterator
digest< Hasher >::end() const
{
    return breeze::end( m_raw_digest ) ;
}

template< typename Hasher >
bool
digest< Hasher >::less::operator()( digest< Hasher > const & d1,
                                    digest< Hasher > const & d2 ) const
{
    return std::lexicographical_compare( d1.begin(), d1.end(),
                                         d2.begin(), d2.end() ) ;
}

//      Stream insertion
//      ================
//
//      Note the logic here: the Hasher keeps an input buffer and only
//      computes a (partial) digest when the buffer is full. Now, we
//      could request the output when the buffer is, for instance, just
//      half-filled. If that triggered the computation we would be in
//      the situation that an output operation would need to modify the
//      object being output. To avoid this, we can make a copy of the
//      hasher and only trigger the computation on the copy.
//      But it would be silly to do the copy here, as in that way we
//      would copy at *every* output operation.
//
//      That's one of the main reasons why we have a digest abstraction:
//      it is an entity on its own and has its own mechanism of
//      construction.
// ---------------------------------------------------------------------------
template< typename Hasher >
std::ostream &
operator <<( std::ostream           & os,
             digest< Hasher > const & d )
{
    int const           bits_per_hex_digit = 4 ;
    int const           bits_per_byte  = Hasher::byte_width ;
    static char const   digits[] = "0123456789abcdef" ;
    unsigned const      mask = ( 1u << bits_per_hex_digit ) - 1 ;

    static_assert( bits_per_byte % bits_per_hex_digit == 0 &&
                   sizeof digits == ( 2 + mask ),
                   "wrong bits_per_hex_digit and/or bits_per_byte" ) ;

    int const           repr_len = Hasher::digest_width / bits_per_hex_digit ;
    char                repr[ repr_len + 1 ] ;
    repr[ repr_len ] = '\0' ;

    typedef typename digest< Hasher >::const_iterator
                        it_type ;
    int                 i = 0 ;
    for ( it_type it( d.begin() ) ; it != d.end() ; ++ it ) {
        for ( int t = bits_per_byte - bits_per_hex_digit ;
                t >= 0 ;
                t -= bits_per_hex_digit ) {
            repr[ i ] = digits[ ( *it >> t ) & mask ] ;
            ++ i ;
        }
    }

    os << repr ;
    return os ;
}

template< typename Hasher >
digest< Hasher >
make_digest( Hasher const & h )
{
    return digest< Hasher >( h ) ;
}

}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
