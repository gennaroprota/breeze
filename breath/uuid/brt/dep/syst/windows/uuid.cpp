// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2016-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/uuid/uuid.hpp"
#include "breath/counting/count.hpp"
#include "breath/diagnostics/assert.hpp"
#include "breath/meta/width.hpp"
#include "breath/random/entropy_source.hpp"
#include "breath/stream/format_saver.hpp"

#include <Windows.h>

#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <ostream>

namespace {

std::uint64_t
to_uint64( FILETIME const & ft )
{
    int const           dword_bits = 32 ;
    return ( static_cast< std::uint64_t >( ft.dwHighDateTime ) << dword_bits ) |
           ft.dwLowDateTime ;
}

}

namespace breath {

uuid::uuid( uuid::variant var, uuid::version ver )
{
    //      Other variants/versions not implemented.
    // -----------------------------------------------------------------------
    BREATH_ASSERT( var == rfc_4122 && ver == time_based ) ;

    //      NT keeps time in FILETIME format, which is 100ns ticks since
    //      Jan 1, 1601. UUIDs use time in 100ns ticks since Oct 15,
    //      1582. The difference is 17 days in Oct + 30 (Nov) + 31 (Dec)
    //      + 18 years and 5 leap days.
    // -----------------------------------------------------------------------
    FILETIME            ft ;
    GetSystemTimeAsFileTime( &ft ) ;
    std::uint64_t const time_stamp =
                                 to_uint64( ft ) +
                                 std::uint64_t( 1000 * 1000 * 10 )
                               * std::uint64_t( 60 * 60 * 24 )
                               * std::uint64_t( 17 + 30 + 31 + 365 * 18 + 5 ) ;

    m_time_low = time_stamp & 0xFFFF'FFFF ;
    m_time_mid = (time_stamp >> 32) & 0xFFFF ;
    m_time_hi_and_version = static_cast< std::uint16_t >(
                            ( (time_stamp >> 48) & 0x0FFF ) | ( 1 << 12 ) ) ;
    entropy_source      es ;
    std::uint32_t const rnd = ( es.next() << 24 ) | ( es.next() << 16 )
                            | ( es.next() << 8 )  |   es.next() ;
    m_clock_seq = static_cast< std::uint16_t >(
                            ( ( rnd >> 4 ) & 0x3fff ) | 0x8000 ) ;

    //      A random MAC address (this is allowed by RFC 4122, and
    //      desirable). To distinguish it from a real MAC address, RFC
    //      4122 requires that the least significant bit of the first
    //      octet be set to 1.
    // -----------------------------------------------------------------------
    for ( std::size_t i = 0 ; i < breath::count( m_node ) ; ++ i ) {
        m_node[ i ] = static_cast< std::uint8_t >( es.next() ) ;
    }
    m_node[ 0 ] |= 1 ;
}

template< typename T >
std::ostream &
output_as_hex( std::ostream & os, T value )
{
    int const           bits_per_hex_digit = 4 ;
    int const           hex_digits_per_value = meta::width< T >::value /
                                               bits_per_hex_digit ;
    os << std::hex ;

    //      About the static_cast: see the note near the declarations of
    //      the class data members. Keep in sync.
    // -----------------------------------------------------------------------
    os << std::setw( hex_digits_per_value ) << static_cast< std::uint32_t >(
                                                                       value ) ;
    return os ;
}

std::ostream &
operator <<( std::ostream & os, uuid const & uu )
{
    format_saver const  saver( os ) ;

    os.fill( '0' ) ;
    os.unsetf( std::ios_base::uppercase ) ;

    output_as_hex( os, uu.m_time_low ) << '-' ;
    output_as_hex( os, uu.m_time_mid ) << '-' ;
    output_as_hex( os, uu.m_time_hi_and_version ) << '-' ;
    output_as_hex( os, uu.m_clock_seq ) << '-' ;
    for ( std::size_t i = 0 ; i < count( uu.m_node ) ; ++ i ) {
        output_as_hex( os, uu.m_node[ i ] ) ;
    }
    return os ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
