// ===========================================================================
//                     Copyright 2006-2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/iteration/begin_end.hpp"
#include <algorithm>
#include <ostream>


//!     \todo Provide a way to extract from streams

namespace breath {

//      Initialization
//      ==============
//
template< typename Hasher >
digest< Hasher >::digest( Hasher hasher_copy )
{
    // should the digest provide word-iterators?? -gps

    hasher_copy.create_digest( m_raw_digest ) ;
}

//      Iteration
//      =========
//
template< typename Hasher >
typename digest< Hasher >::const_iterator
digest< Hasher >::begin() const
{
    return breath::begin( m_raw_digest ) ;
}

template< typename Hasher >
typename digest< Hasher >::const_iterator
digest< Hasher >::end() const
{
    return breath::end( m_raw_digest ) ;
}

//      Equality comparison
//      ===================
//
template< typename Hasher >
bool
digest< Hasher >::is_equal( digest< Hasher > const & other ) const
{
    return std::equal( this->begin(), this->end(), other.begin() ) ;
}

//      Stream insertion
//      ================
//
//      Note the logic here: the Hasher keeps an input buffer
//      and only computes a (partial) digest when the buffer is
//      full. Now, we could request the output when the buffer
//      is, for instance, just half-filled. If that triggered
//      the computation we would be in the situation that an
//      output operation would need to modify the object being
//      output. To avoid this, we can make a copy of the
//      hasher and only trigger the computation on the copy.
//      But it would be silly to do the copy here, as in that way
//      we would copy at *every* output operation.
//
//      That's one of main reason why we have a digest abstraction:
//      it is an entity on its own and has its own mechanism of
//      construction.
// -----------------------------------------------------------------------
template< typename Ch, typename Tr, typename Hasher >
std::basic_ostream< Ch, Tr > &
operator <<( std::basic_ostream< Ch, Tr >   & os,
             breath::digest< Hasher > const & d )
{
    enum
    {
        bits_per_digit = 4, // hex base
        bits_per_byte  = Hasher::byte_width
    } ;

    static char const   digits[] = "0123456789abcdef" ;
    unsigned const      mask = ( 1u << bits_per_digit ) - 1 ;

    static_assert(
                    0 < bits_per_digit && bits_per_digit < bits_per_byte
                      && sizeof digits == ( 2 + mask ),
                    "wrong bits_per_digit and/or bits_per_byte" ) ;

    typedef typename breath::digest< Hasher >::const_iterator
                        it_type ;
    for ( it_type it( d.begin() ) ; it != d.end() ; ++ it ) {
        for ( int t = bits_per_byte - bits_per_digit ;
                t >= 0 ;
                t -= bits_per_digit ) {
            os.put( os.widen( digits[ *it >> t & mask ] ) ) ;
        }
    }

    return os ;
}

template< typename Hasher >
breath::digest< Hasher > make_digest( Hasher const & h )
{
    return digest< Hasher >( h ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
