// ===========================================================================
//                     Copyright 2016-2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/meta/width.hpp"

namespace breeze_ns {
namespace crc_private {

//      reflect():
//      ==========
//
//      Reverses the order of the least significant 'count' bits in 'n'.
//
//      Not optimized, because it's only used either in constexpr
//      contexts or outside the input accumulation loop (it's not called
//      for every input byte). (TODO?)
// ---------------------------------------------------------------------------
template< int count, typename Unsigned >
constexpr Unsigned
reflect( Unsigned n )
{
    Unsigned            result = n ;

    for ( int i = 0 ; i < count ; ++ i ) {
        auto const          mask = static_cast< Unsigned >(
            Unsigned( 1 ) << ( count - 1 - i ) ) ;
        if ( ( n & ( Unsigned( 1 ) << i ) ) != 0 ) {
            result |= mask ;
        } else {
            result &= static_cast< Unsigned >( ~mask ) ;
        }
    }

    return result ;
}

//      zeroize_extra_bits():
//      =====================
//
//      Leaves only the least significant 'count' bits in 'n', zeroizing
//      all the other bits, if any.
// ---------------------------------------------------------------------------
template< int count, typename Unsigned >
void zeroize_extra_bits( Unsigned & n )
{
    n &= Unsigned( -1 ) >> ( breeze::meta::width< Unsigned >::value - count ) ;
}

static_assert( reflect< 4, std::uint32_t >( 0b10101100 ) == 0b10100011,
               "sanity check for the reflect() template" ) ;

//      crc_cache:
//      ==========
//
//      CRC cache for byte-sized values. This provides simple
//      memoization.
// ---------------------------------------------------------------------------
template< typename CrcTraits >
class crc_cache
{
public:
    typedef typename CrcTraits::value_type
                        value_type ;
    static int const    size = 256 ;

    constexpr           crc_cache() noexcept ;

    constexpr value_type
                        operator[]( int index ) const noexcept ;

private:
    value_type          m_data[ size ] ;
} ;


template< typename CrcTraits >
constexpr crc_cache< CrcTraits >::crc_cache() noexcept
    :   m_data()
{
    value_type const    top_bit = value_type( 1 )  << ( CrcTraits::width - 1 ) ;
    value_type const    mask    = value_type( -1 ) >>
        ( meta::width< value_type >::value - CrcTraits::width ) ;

    for ( int i = 0 ; i < size ; ++ i ) {
        auto                crc = static_cast< value_type >( i ) ;

        if ( CrcTraits::reflect_in ) {
            crc = reflect< 8 >( crc ) ;
        }

        if ( CrcTraits::width > 8 ) {
            crc = static_cast< value_type >( crc << ( CrcTraits::width - 8 ) ) ;
        }

        for ( int k = 0 ; k < 8 ; ++ k ) {
            crc = static_cast< value_type >( mask & ( crc & top_bit
                ? ( crc << 1 ) ^ CrcTraits::poly
                :   crc << 1
                ) ) ;
        }

        if ( CrcTraits::reflect_in ) {
            crc = reflect< CrcTraits::width >( crc ) ;
        }

        m_data[ i ] = crc ;
    }
}

template< typename CrcTraits >
constexpr typename crc_cache< CrcTraits >::value_type
crc_cache< CrcTraits >::operator[]( int index ) const noexcept
{
    return m_data[ index ] ;
}

}

template< typename Traits >
constexpr crc< Traits >::crc() noexcept
    :   m_current( init )
{
    if ( reflect_in ) {
        m_current = crc_private::reflect< width >( m_current ) ;
    }
}

template< typename Traits >
template< typename InputIter >
constexpr crc< Traits >::crc( InputIter first, InputIter last )
    :   crc()
{
    accumulate( first, last ) ;
}

template< typename Traits >
template< typename InputIter >
constexpr void
crc< Traits >::accumulate( InputIter first, InputIter last )
{
    int const           char_bit = 8 ;
    int const           mask     = ( 1 << char_bit ) - 1 ;
    bool const          can_shift = char_bit <
                                        meta::width< value_type >::value ;

    //      This 'if' could be resolved at compile time. But since the
    //      test is done once per accumulation, we didn't bother with
    //      template specializations and such, in order to achieve that.
    //      We could use 'if constexpr' when we'll require C++17 or
    //      later, though.
    // -----------------------------------------------------------------------
    if ( reflect_in ) {
        while ( first != last ) {
            value_type          new_current =
                s_cache[ ( m_current ^ *first ) & mask ] ;
            if ( can_shift ) {
                new_current = static_cast< value_type >(
                    new_current ^ ( m_current >> char_bit ) ) ;
            }
            m_current = new_current ;
            ++ first ;
        }
    } else {
        while ( first != last ) {
            value_type          new_current =
                s_cache[ ( ( m_current >> ( width - char_bit ) ) ^ *first )
                    & mask ] ;
            if ( can_shift ) {
                new_current = static_cast< value_type >(
                    new_current ^ ( m_current << char_bit ) ) ;
            }
            m_current = new_current ;
            ++ first ;
        }
    }

    crc_private::zeroize_extra_bits< width >( m_current ) ;
}

template< typename Traits >
constexpr void
crc< Traits >::accumulate( char c ) noexcept
{
    accumulate( &c, &c + 1 ) ;
}

template< typename Traits >
constexpr typename crc< Traits >::value_type
crc< Traits >::value() const noexcept
{
    value_type          result = m_current ;
    if ( reflect_in != reflect_out ) {
        result = crc_private::reflect< width >( result ) ;
    }

    result ^= xor_out ;
    return result ;
}

template< typename Traits >
constexpr crc_private::crc_cache< Traits >
crc< Traits >::s_cache ;

}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
