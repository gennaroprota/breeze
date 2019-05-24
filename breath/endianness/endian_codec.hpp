// ===========================================================================
//                     Copyright 2006-2007 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Converter from/to byte sequences representations.
//
//      NOTE: to avoid overcomplicated syntax (template members of class
//      templates), this file doesn't have a corresponding .tpp file.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_KF72jjCHTZHZqOBTMYHp95Fij2ZyYgaS
#define BREATH_GUARD_KF72jjCHTZHZqOBTMYHp95Fij2ZyYgaS

#include "breath/meta/has_sign.hpp"
#include "breath/meta/width.hpp"
#include <cstddef>
#include <iterator>

namespace breath {
//! \cond
namespace endian_codec_private {

template< typename T, typename Byte >
class width_ratio
{
    static_assert( meta::width< T >::value % meta::width< Byte >::value == 0,
                   "a T must be wide exactly n Bytes" ) ;

    enum { q = meta::width< T >::value / meta::width< Byte >::value } ;

public:
    // how many Bytes do we need to store a T?
    static std::size_t const
                        value = q > 1 ? q : 1 ;
} ;

template< typename T, typename Byte >
std::size_t const
width_ratio< T, Byte >::value ;

template< typename T, std::size_t n, typename Byte >
class width_ratio< T[ n ], Byte >
{
public:
    static std::size_t const
                        value = n * width_ratio< T, Byte >::value ;
} ;

template<
    typename EndianPolicy,
    typename T,
    typename Byte,
    //      Hiding this parameter from the user is the reason why we
    //      have endian_codec_private::endian_codec.
    std::size_t n = endian_codec_private::width_ratio< T, Byte >::value
>
class endian_codec
{
    static_assert( ! meta::has_sign< T >::value &&
                   ! meta::has_sign< Byte >::value,
                   "T and Byte can't have a sign") ;

    typedef EndianPolicy
                        policy ;
    typedef endian_codec< policy, T, Byte, n - 1 >
                        next ;
    enum {              shift = meta::width< Byte >::value } ;

public:
    //!     Writes (encodes) the value \c value as a sequence of \c
    //!     Bytes, according to \c EndianPolicy and starting with \c
    //!     dest.
    // -----------------------------------------------------------------------
    template< typename ByteRandomIter >
    static void         encode( T const & value, ByteRandomIter dest )
    {
        // write the least significant part
        dest[ policy::template index< T, Byte, n - 1 >()
            ] = static_cast< Byte >( value ) ;
        next::encode(
            // '* (n > 1)' silences spurious warnings
            n > 1 ? ( value >> shift * (n > 1) ) : 0,
            dest ) ;
    }

    //!     \return
    //!         The value of type \c T encoded, according to \c
    //!         EndianPolicy, as the sequence of \c Bytes that begins
    //!         with \c source.
    // -----------------------------------------------------------------------
    template< typename ByteRandomIter >
    static T            decode( ByteRandomIter source )
    {
        return source[ policy:: template index< T, Byte, n - 1 >() ]
             | next::decode( source ) << shift ;
    }
} ;

template< typename EndianPolicy, typename T, typename Byte >
class endian_codec< EndianPolicy, T, Byte, 0 >
{
public:
    template< typename ByteIter >
    static void         encode( T const &, ByteIter )
    {
    }

    template< typename ByteIter >
    static T            decode( ByteIter )
    {
        return 0 ;
    }
} ;

}
//! \endcond

//      little_endian_policy:
//      =====================
//
//!     Little-endian policy for endian_codec.
// ---------------------------------------------------------------------------
//
//      NOTE:
//
//      There's no general guarantee that we can infer the load/store
//      order via a single Endianness template parameter: the ordering
//      also depends on the types T and Byte.
//
//      Fortunately, dependency on all of the three variables is not
//      common. Thus, our default policies, defined below, take the
//      endianness type only into account. Your will need to provide
//      your own policy for more exotic cases (e.g. if you are dealing
//      with PDP-11 endianness).
// ---------------------------------------------------------------------------
class little_endian_policy
{
public:
    // n == 0 for the most significant byte
    //
    template< typename T, typename Byte, std::size_t n >
    static std::size_t  index()
    {
        return endian_codec_private::width_ratio< T, Byte >::value - 1 - n ;
    }

    template< typename T, typename Byte >
    static std::size_t  index( std::size_t n )
    {
        return endian_codec_private::width_ratio< T, Byte >::value - 1 - n ;
    }
} ;

//      big_endian_policy:
//      ==================
//
//!     Big-endian policy for endian_codec.
// ---------------------------------------------------------------------------
class big_endian_policy
{
public:
    template< typename T, typename Byte, std::size_t n >
    static std::size_t  index()
    {
        return n ;
    }

    template< typename T, typename Byte >
    static std::size_t  index( std::size_t n )
    {
        return n ;
    }
} ;

//      endian_codec:
//      =============
//
//!     Converts generic values to/from (byte-)sequence
//!     representations.
//!
//!     In general, \c endian_codec can read and store a representation
//!     of a value as a sequence of smaller units, regardless of their
//!     widths. It is mostly useful to read and write values
//!     independently of the endianness they are stored in, as long as
//!     the endianness type is known.
//!
//!     It is only designed for reads and writes in memory.
//!
//!     \par Type requirements
//!         \c T and \c Byte shall be unsigned integral types.
//!         There's no requirement that \c Byte have a smaller em width
//!         than \c T, but the width of \c Byte must evenly divide the
//!         width of \c T.
//!
//!     \warning
//!         Given its generality it might be a good idea to rename
//!         this to something like "order_codec" or similar; feedback
//!         is welcome.
//!
//!     \todo Check this; is it true for user-policies?
// ---------------------------------------------------------------------------
template<
    typename EndianPolicy,
    typename T,
    typename Byte
>
class endian_codec
{
private:
    static std::size_t const
                        n = endian_codec_private::
                              width_ratio< T, Byte >::value ;
public:
    static std::size_t const
                        required_count = n ; // gps experimental

    //!     Writes (encodes) the value \c value as a sequence of \c
    //!     Bytes, according to \c EndianPolicy and starting with \c
    //!     dest.
    // -----------------------------------------------------------------------
    template< typename ByteRandomIter >
    static void         encode( T const & value, ByteRandomIter dest )
    {
        endian_codec_private::endian_codec< EndianPolicy,
                                            T,
                                            Byte,
                                            n >::encode( value, dest ) ;
    }

    //!     \return
    //!         The value of type \c T encoded, according to \c
    //!         EndianPolicy, as the sequence of \c Bytes that begins
    //!         with \c source.
    // -----------------------------------------------------------------------
    template< typename ByteRandomIter >
    static T            decode( ByteRandomIter source )
    {
        return endian_codec_private::endian_codec< EndianPolicy,
                                                   T,
                                                   Byte,
                                                   n >::decode( source ) ;
    }
} ;

template< typename EndianPolicy,
          typename T,
          typename Byte >
std::size_t const
endian_codec< EndianPolicy, T, Byte >::required_count ;


//!     Convenience wrapper around \c endian_codec::encode();
//!     \c endian_store< EndianPolicy( value, it ) > is equivalent to:
//!
//!     <code>
//!         typedef typename std::iterator_traits< ByteRandomIter >::value_type
//!                             Byte ;
//!         breath::endian_codec< EndianPolicy, T, Byte >::encode( value, it ) ;
//!     </code>
// ---------------------------------------------------------------------------
template< typename EndianPolicy, typename T, typename ByteRandomIter >
void
endian_store( T const & value, ByteRandomIter it )
{
    typedef typename std::iterator_traits< ByteRandomIter >::value_type
                        Byte ;
    breath::endian_codec< EndianPolicy, T, Byte >::encode( value, it ) ;
}

//!     Conveniente wrapper around \c endian_codec::decode();
//!     \c endian_load< EndianPolicy >( it ) is equivalent to:
//!
//!     <code>
//!         typedef typename std::iterator_traits< ByteRandomIter >::value_type
//!                             Byte ;
//!         return breath::endian_codec< EndianPolicy, T, Byte >::decode( it ) ;
//!     </code>
// ---------------------------------------------------------------------------
template< typename EndianPolicy, typename T, typename ByteRandomIter >
T
endian_load( ByteRandomIter it )
{
    typedef typename std::iterator_traits< ByteRandomIter >::value_type
                        Byte ;
    return breath::endian_codec< EndianPolicy, T, Byte >
        ::decode( it ) ;
}

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
