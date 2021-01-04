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

#include "breeze/porting/dependent_source.hpp"
#include BREEZE_DEPENDENT_SOURCE( system_family, system_time_for_uuid.cpp )

#include "breeze/uuid/uuid.hpp"
#include "breeze/diagnostics/assert.hpp"
#include "breeze/endianness/endian_codec.hpp"
#include "breeze/iteration/begin_end.hpp"
#include "breeze/random/entropy_source.hpp"
#include "breeze/text/string_constant.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <ostream>

namespace breeze_ns {
namespace           {

//      adjusted_system_time():
//      =======================
//
//      Gets the system time and compensates for the fact that the
//      system clock resolution is (or may be) higher than 100ns, which
//      is the resolution that would be required for UUIDs.
//
//      Note: this function is the reason why the uuid class is not
//      thread-safe.
// ---------------------------------------------------------------------------
std::uint64_t
adjusted_system_time()
{
    int const           max_uuids_per_tick =
                             breeze::uuid_private::max_uuids_per_system_tick() ;
    static int          uuids_on_this_tick ; // no initializer, see if below
    static std::uint64_t
                        last_time ;          // no initializer, see if below
    static bool         is_first_call = true ;

    if ( is_first_call ) {
        uuids_on_this_tick = 1 ;
        last_time = breeze::uuid_private::system_time_for_uuid() ;
        is_first_call = false ;
        return last_time ;
    }

    std::uint64_t       now ;
    while ( true ) {
        now = breeze::uuid_private::system_time_for_uuid() ;
        if ( last_time != now ) {
            last_time = now ;
            uuids_on_this_tick = 1 ;
            break ;
        } else if ( uuids_on_this_tick < max_uuids_per_tick ) {
            ++ uuids_on_this_tick ;
            break ;
        }

        // Too many UUIDs are being requested on the same tick: busy wait...
    }

    return now + ( uuids_on_this_tick - 1 ) ;
}

}


uuid::uuid() noexcept
    :   m_octets()
{
}

uuid::uuid( uuid::variant_type var, uuid::version_type ver )
{
    //      Other variants/versions not implemented.
    // -----------------------------------------------------------------------
    BREEZE_ASSERT( var == rfc_4122 && ver == time_based ) ;

    std::uint64_t const time_stamp = adjusted_system_time() ;

    std::uint32_t const time_low = time_stamp & 0xFFFF'FFFF ;
    std::uint16_t const time_mid = (time_stamp >> 32) & 0xFFFF ;
    std::uint16_t const time_hi_and_version = static_cast< std::uint16_t >(
                            ( (time_stamp >> 48) & 0x0FFF ) | ( 1 << 12 ) ) ;

    breeze::endian_store< big_endian_policy >( time_low, &m_octets[ 0 ] ) ;
    breeze::endian_store< big_endian_policy >( time_mid, &m_octets[ 4 ] ) ;
    breeze::endian_store< big_endian_policy >( time_hi_and_version,
                                                         &m_octets[ 6 ] ) ;

    entropy_source      es ;
    std::uint32_t const rnd = ( es.next() << 16 ) |
                              ( es.next() << 8 )  |
                                es.next() ;
    std::uint16_t const clock_seq = static_cast< std::uint16_t >(
                              ( ( rnd >> 4 ) & 0x3fff ) | 0x8000 ) ;

    breeze::endian_store< big_endian_policy >( clock_seq, &m_octets[ 8 ] ) ;

    //      A random MAC address (this is allowed by RFC 4122, and
    //      desirable). To distinguish it from a real MAC address, RFC
    //      4122 requires that the least significant bit of the first
    //      octet be set to 1.
    // -----------------------------------------------------------------------
    for ( int i = 10 ; i < 16 ; ++ i ) {
        m_octets[ i ] = static_cast< std::uint8_t >( es.next() ) ;
    }
    m_octets[ 10 ] |= 1 ;
}

uuid::variant_type
uuid::variant() const
{
    //      Reference: RFC 4122
    // -----------------------------------------------------------------------
    int const           high3 = m_octets[ 8 ] >> 5 ;

    if ( ( high3 & 0b100 ) == 0 ) {
        return ncs ;
    } else if ( ( high3 & 0b110 ) == 0b100 ) {
        return rfc_4122 ;
    } else if ( ( high3 & 0b111 ) == 0b110 ) {
        return microsoft ;
    } else {
        BREEZE_ASSERT( ( high3 & 0b111 ) == 0b111 ) ;
        return future ;
    }
}

uuid::version_type
uuid::version() const
{
    //      Reference: RFC 4122
    // -----------------------------------------------------------------------
    int const           version_number = m_octets[ 6 ] >> 4 ;

    BREEZE_ASSERT( 1 <= version_number && version_number <= 5 ) ;
    return static_cast< version_type >( version_number ) ;
}

uuid
uuid::nil() noexcept
{
    return uuid() ;
}

bool
uuid::is_equal( uuid const & other ) const noexcept
{
    return std::equal( breeze::cbegin( m_octets ), breeze::cend( m_octets ),
                       breeze::cbegin( other.m_octets ) ) ;
}

bool
uuid::less::operator()( uuid const & u1, uuid const & u2 ) const noexcept
{
    return std::lexicographical_compare( breeze::cbegin( u1.m_octets ),
                                         breeze::cend(   u1.m_octets ),
                                         breeze::cbegin( u2.m_octets ),
                                         breeze::cend(   u2.m_octets ) ) ;
}

std::ostream &
operator <<( std::ostream & os, uuid const & uu )
{
    int const           bit_count = 128 ;
    int const           bits_per_hex_digit = 4 ;
    int const           hyphen_count = 4 ;
    auto const &        digits = lowercase_hex_digits ;

    int const           len = bit_count / bits_per_hex_digit + hyphen_count ;
    char                repr[ len + 1 ] ;
    repr[ len ] = '\0' ;

    int to = 0 ;
    for ( int i = 0 ; i < bit_count / 8 ; ++ i ) {
        repr[ to ] = digits[ uu.m_octets[ i ] >> 4 ] ;
        ++ to ;
        repr[ to ] = digits[ uu.m_octets[ i ] & 0x0f ] ;
        ++ to ;

        if ( i == 3 || i == 5 || i == 7 || i == 9 ) {
            repr[ to ] = '-' ;
            ++ to ;
        }
    }

    os << repr ;
    return os ;
}

}
