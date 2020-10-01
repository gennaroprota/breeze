// ===========================================================================
//                     Copyright 2006-2007 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Converter from/to byte sequence representations.
//
//      NOTE: to avoid overcomplicated syntax (template members of class
//      templates), this file doesn't have a corresponding .tpp file.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_KF72jjCHTZHZqOBTMYHp95Fij2ZyYgaS
#define BREATH_GUARD_KF72jjCHTZHZqOBTMYHp95Fij2ZyYgaS

#include "breath/top_level_namespace.hpp"
#include "breath/meta/has_sign.hpp"
#include "breath/meta/width.hpp"
#include <cstddef>
#include <iterator>

namespace breath_ns {
//!\cond implementation
namespace endian_codec_private {

template< typename T, typename Byte >
class width_ratio
{
    enum { q = meta::width< T >::value / meta::width< Byte >::value } ;

    static_assert( q == 0 ||
                     meta::width< T >::value % meta::width< Byte >::value == 0,
                   "a T must fit in one Byte or be wide exactly n Bytes" ) ;


public:
    // how many Bytes do we need to store a T?
    static std::ptrdiff_t const
                        value = q > 1 ? q : 1 ;
} ;

template< typename T, typename Byte >
std::ptrdiff_t const
width_ratio< T, Byte >::value ;

template< typename T, std::ptrdiff_t n, typename Byte >
class width_ratio< T[ n ], Byte >
{
public:
    static std::ptrdiff_t const
                        value = n * width_ratio< T, Byte >::value ;
} ;

template<
    typename EndianPolicy,
    typename T,
    typename Byte,
    //      Hiding this parameter from the user is the reason why we
    //      have endian_codec_private::endian_codec.
    std::ptrdiff_t n = endian_codec_private::width_ratio< T, Byte >::value
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

public:
    //!     Writes (encodes) the value \c value as a sequence of \c
    //!     Bytes, according to \c EndianPolicy and starting with \c
    //!     dest.
    // -----------------------------------------------------------------------
    template< typename ByteOutputIter >
    static void         encode( T const & value, ByteOutputIter dest )
    {
        int const           shift_amount =
            policy:: template shift_amount< T, Byte, n - 1 >() ;

        *dest = static_cast< Byte >( value >> shift_amount ) ;
        next::encode( value, ++ dest ) ;
    }

    //!     \return
    //!         The value of type \c T encoded, according to \c
    //!         EndianPolicy, as the sequence of \c Bytes that begins
    //!         with \c source.
    // -----------------------------------------------------------------------
    template< typename ByteInputIter >
    static T            decode( ByteInputIter source )
    {
        int const           shift_amount =
            policy:: template shift_amount< T, Byte, n - 1 >() ;

        T const             temp = T( *source ) << shift_amount ;
        return  temp | next::decode( ++ source ) ;
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
//!\endcond

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
//      endianness type only into account. You will need to provide your
//      own policy for more exotic cases (e.g. if you are dealing with
//      PDP-11 endianness).
// ---------------------------------------------------------------------------
class little_endian_policy
{
public:
    // n == width_ratio - 1 to produce the first Byte
    //
    template< typename T, typename Byte, std::ptrdiff_t n >
    static int          shift_amount()
    {
        return ( endian_codec_private::width_ratio< T, Byte >::value - 1 - n ) *
            meta::width< Byte >::value ;
    }

    template< typename T, typename Byte >
    static std::ptrdiff_t
                        index( std::ptrdiff_t n )
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
    template< typename T, typename Byte, std::ptrdiff_t n >
    static int          shift_amount()
    {
        return n * meta::width< Byte >::value ;
    }

    template< typename T, typename Byte >
    static std::ptrdiff_t
                        index( std::ptrdiff_t n )
    {
        return n ;
    }
} ;

//      endian_codec:
//      =============
//
//!     \copybrief endian_codec.hpp
//!
//!     Converts generic values to/from (byte-)sequence
//!     representations.
//!
//!     In general, \c endian_codec can read and store a representation
//!     of a value as a sequence of smaller units, regardless of their
//!     widths. It is mostly useful to read and write values
//!     independently of the endianness they are stored in, as long as
//!     the endianness type is known.
//!
//!     \par Type requirements
//!         \c T and \c Byte shall be integral types with no sign.
//!         The width of \c T must be smaller than the width of \c Byte
//!         (e.g. you can store a 32-bit integer into a 64-bit one) or
//!         an exact multiple of it.
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
    static std::ptrdiff_t const
                        n = endian_codec_private::
                              width_ratio< T, Byte >::value ;
public:
    static std::ptrdiff_t const
                        required_count = n ; // gps experimental

    //!     Writes (encodes) the value \c value as a sequence of \c
    //!     Bytes, according to \c EndianPolicy and starting with \c
    //!     dest.
    // -----------------------------------------------------------------------
    template< typename ByteOutputIter >
    static void         encode( T const & value, ByteOutputIter dest )
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
    template< typename ByteInputIter >
    static T            decode( ByteInputIter source )
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
std::ptrdiff_t const
endian_codec< EndianPolicy, T, Byte >::required_count ;


//      endian_store:
//      =============
//
//!     \brief Convenience wrapper around \c endian_codec::encode()
//!
//!     \c endian_store< EndianPolicy( value, it ) > is equivalent to:
//!
//!     <code>
//!         typedef typename std::iterator_traits< ByteOutputIter >::value_type
//!                             Byte ;
//!         breath::endian_codec< EndianPolicy, T, Byte >::encode( value, it ) ;
//!     </code>
// ---------------------------------------------------------------------------
template< typename EndianPolicy, typename T, typename ByteOutputIter >
void
endian_store( T const & value, ByteOutputIter it )
{
    typedef typename std::iterator_traits< ByteOutputIter >::value_type
                        Byte ;
    breath::endian_codec< EndianPolicy, T, Byte >::encode( value, it ) ;
}

//      endian_load:
//      ============
//
//!     \brief Convenience wrapper around \c endian_codec::decode()
//!
//!     \c endian_load< EndianPolicy >( it ) is equivalent to:
//!
//!     <code>
//!         typedef typename std::iterator_traits< ByteInputIter >::value_type
//!                             Byte ;
//!         return breath::endian_codec< EndianPolicy, T, Byte >::decode( it ) ;
//!     </code>
// ---------------------------------------------------------------------------
template< typename EndianPolicy, typename T, typename ByteInputIter >
T
endian_load( ByteInputIter it )
{
    typedef typename std::iterator_traits< ByteInputIter >::value_type
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
