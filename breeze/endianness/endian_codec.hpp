// ===========================================================================
//                     Copyright 2006-2007 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Converter from/to "byte" sequence representations.
//
//      NOTE: to avoid overcomplicated syntax (template members of class
//      templates), this file doesn't have a corresponding .tpp file.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_KF72jjCHTZHZqOBTMYHp95Fij2ZyYgaS
#define BREEZE_GUARD_KF72jjCHTZHZqOBTMYHp95Fij2ZyYgaS

#include "breeze/top_level_namespace.hpp"
#include "breeze/meta/has_sign.hpp"
#include "breeze/meta/width.hpp"
#include <cstddef>
#include <iterator>

namespace breeze_ns {
//!\cond implementation
namespace endian_codec_private {

//      How many Bytes do we need to store a T?
template< typename T, typename Byte >
class required_count
{
    enum { q = meta::width< T >::value / meta::width< Byte >::value } ;

    static_assert( q == 0 ||
                     meta::width< T >::value % meta::width< Byte >::value == 0,
                   "a T must fit in one Byte or be wide exactly n Bytes" ) ;


public:
    static std::ptrdiff_t const
                        value = q > 1 ? q : 1 ;
} ;

template< typename T, typename Byte >
std::ptrdiff_t const
required_count< T, Byte >::value ;

template< typename T, std::ptrdiff_t n >
class required_count< T[ n ], T >
{
public:
    static std::ptrdiff_t const
                        value = n ;
} ;

template<
    typename EndianPolicy,
    typename T,
    typename Byte,
    //      Hiding this parameter from the user is the reason why we
    //      have endian_codec_private::endian_codec.
    std::ptrdiff_t n = endian_codec_private::required_count< T, Byte >::value
>
class endian_codec
{
    static_assert( ! meta::has_sign< T >::value &&
                   ! meta::has_sign< Byte >::value,
                   "T and Byte can't have a sign") ;

    typedef endian_codec< EndianPolicy, T, Byte, n - 1 >
                        next ;

    enum { shift_amount = meta::width< Byte >::value } ;

public:
    template< typename RandomIter >
    static void         encode( T value, RandomIter dest )
    {
        dest[ EndianPolicy::template index< T, Byte >( n - 1 )
            ] = static_cast< Byte >( value ) ;
        next::encode(
            // '* (n > 1)' silences spurious warnings
            n > 1 ? ( value >> shift_amount * (n > 1) ) : 0
            , dest ) ;
    }

    template< typename RandomIter >
    static T            decode( RandomIter source )
    {
        return source[ EndianPolicy:: template index< T, Byte >( n - 1 ) ]
             | next::decode( source ) << shift_amount ;
    }
} ;

template< typename EndianPolicy, typename T, typename Byte >
class endian_codec< EndianPolicy, T, Byte, 0 >
{
public:
    template< typename Iter >
    static void         encode( T, Iter )
    {
    }

    template< typename Iter >
    static T            decode( Iter )
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
//!
//!     \see
//!         big_endian_policy.
// ---------------------------------------------------------------------------
//
//      NOTE:
//
//      There's no general guarantee that we can infer the load/store
//      order via a single Endianness template parameter: the ordering
//      might also depend on the types T and Byte.
//
//      Fortunately, dependency on all of the three variables is not
//      common. Thus, our default policies, defined below, take the
//      endianness type only into account.
// ---------------------------------------------------------------------------
class little_endian_policy
{
public:

    template< typename T, typename Byte >
    static std::ptrdiff_t
                        index( std::ptrdiff_t n )
    {
        return endian_codec_private::required_count< T, Byte >::value - 1 - n ;
    }
} ;

//      big_endian_policy:
//      ==================
//
//!     Big-endian policy for endian_codec.
//!
//!     \see
//!         little_endian_policy.
// ---------------------------------------------------------------------------
class big_endian_policy
{
public:
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
//!     In general, `endian_codec` can read and store a representation
//!     of a value as a sequence of (possibly smaller) units, regardless
//!     of their widths. It is mostly useful to read and write values
//!     independently of the endianness they are stored in, as long as
//!     the endianness type is known.
//!
//!     \par Type requirements
//!         `T` and `Byte` shall be integral types with no sign. The
//!         width of `T` must be smaller than the width of `Byte` (e.g.
//!         you can store a 32-bit integer into a 64-bit one) or an
//!         exact multiple of it.
//!
//!     \warning
//!         Given its generality it might be a good idea to rename this
//!         to something like "order_codec" or similar; feedback is
//!         welcome.
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
public:
    static std::ptrdiff_t const
                        required_count =
        endian_codec_private::required_count< T, Byte >::value ;

    //!     Writes (encodes) the value `value` into a range starting
    //!     with `dest`, according to `EndianPolicy`.
    // -----------------------------------------------------------------------
    template< typename RandomIter >
    static void         encode( T value, RandomIter dest )
    {
        endian_codec_private::endian_codec<
            EndianPolicy, T, Byte >::encode( value, dest ) ;
    }

    //!     \return
    //!         The value of type `T` encoded, according to
    //!         `EndianPolicy`, in a range that begins with `source`.
    //!
    //!     \note
    //!         The `value_type` of `RandomIter` can be larger than
    //!         `Byte`.
    // -----------------------------------------------------------------------
    template< typename RandomIter >
    static T            decode( RandomIter source )
    {
        return endian_codec_private::endian_codec<
            EndianPolicy, T, Byte >::decode( source );
    }
} ;

template< typename EndianPolicy,
          typename T,
          typename Byte >
std::ptrdiff_t const
endian_codec< EndianPolicy, T, Byte >::required_count ;


//      endian_store():
//      ===============
//
//!     \brief Convenience wrapper around `endian_codec::encode()` which
//!            derives `Byte` from the iterator type.
//!
//!     `endian_store< EndianPolicy >( value, it )` is equivalent to:
//!
//!     ```
//!         typedef typename std::iterator_traits< RandomIter >::value_type
//!                             Byte ;
//!         breeze::endian_codec< EndianPolicy, T, Byte >::encode( value, it ) ;
//!     ```
//!
//!     \note
//!         This can't be used for purely output iterators, because they
//!         don't have a notion of `value_type`.
// ---------------------------------------------------------------------------
template< typename EndianPolicy, typename T, typename RandomIter >
void
endian_store( T const & value, RandomIter it )
{
    typedef typename std::iterator_traits< RandomIter >::value_type
                        Byte ;
    breeze::endian_codec< EndianPolicy, T, Byte >::encode( value, it ) ;
}

//      endian_load():
//      ==============
//
//!     \brief Convenience wrapper around `endian_codec::decode()` which
//!            derives `Byte` from the iterator type.
//!
//!     `endian_load< EndianPolicy, T >( it )` is equivalent to:
//!
//!     ```
//!         typedef typename std::iterator_traits< RandomIter >::value_type
//!                             Byte ;
//!         return breeze::endian_codec< EndianPolicy, T, Byte >::decode( it ) ;
//!     ```
// ---------------------------------------------------------------------------
template< typename EndianPolicy, typename T, typename RandomIter >
T
endian_load( RandomIter it )
{
    typedef typename std::iterator_traits< RandomIter >::value_type
                        Byte ;
    return breeze::endian_codec< EndianPolicy, T, Byte >::decode( it ) ;
}

}

#endif
