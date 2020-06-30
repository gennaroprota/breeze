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

#include "breath/porting/dependent_code.hpp"
#include BREATH_DEPENDENT_CODE( system, system_time_for_uuid.cpp )

#include "breath/uuid/uuid.hpp"
#include "breath/diagnostics/assert.hpp"
#include "breath/endianness/endian_codec.hpp"
#include "breath/iteration/begin_end.hpp"
#include "breath/random/entropy_source.hpp"
#include "breath/stream/stream_equivalent.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <ostream>

namespace breath {
namespace        {

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
                             breath::uuid_private::max_uuids_per_system_tick() ;
    static int          uuids_on_this_tick ; // no initializer, see if below
    static std::uint64_t
                        last_time ;          // no initializer, see if below
    static bool         is_first_call = true ;

    if ( is_first_call ) {
        uuids_on_this_tick = 1 ;
        last_time = breath::uuid_private::system_time_for_uuid() ;
        is_first_call = false ;
        return last_time ;
    }

    std::uint64_t       now ;
    while ( true ) {
        now = breath::uuid_private::system_time_for_uuid() ;
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
    BREATH_ASSERT( var == rfc_4122 && ver == time_based ) ;

    std::uint64_t const time_stamp = adjusted_system_time() ;

    std::uint32_t const time_low = time_stamp & 0xFFFF'FFFF ;
    std::uint16_t const time_mid = (time_stamp >> 32) & 0xFFFF ;
    std::uint16_t const time_hi_and_version = static_cast< std::uint16_t >(
                            ( (time_stamp >> 48) & 0x0FFF ) | ( 1 << 12 ) ) ;

    breath::endian_store< big_endian_policy >( time_low, &m_octets[ 0 ] ) ;
    breath::endian_store< big_endian_policy >( time_mid, &m_octets[ 4 ] ) ;
    breath::endian_store< big_endian_policy >( time_hi_and_version,
                                                         &m_octets[ 6 ] ) ;

    entropy_source      es ;
    std::uint32_t const rnd = ( es.next() << 16 ) |
                              ( es.next() << 8 )  |
                                es.next() ;
    std::uint16_t const clock_seq = static_cast< std::uint16_t >(
                              ( ( rnd >> 4 ) & 0x3fff ) | 0x8000 ) ;

    breath::endian_store< big_endian_policy >( clock_seq, &m_octets[ 8 ] ) ;

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
uuid::variant() const noexcept
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
        BREATH_ASSERT( ( high3 & 0b111 ) == 0b111 ) ;
        return future ;
    }
}

uuid::version_type
uuid::version() const noexcept
{
    //      Reference: RFC 4122
    // -----------------------------------------------------------------------
    int const           version_number = m_octets[ 6 ] >> 4 ;

    BREATH_ASSERT( 1 <= version_number && version_number <= 5 ) ;
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
    return std::equal( breath::cbegin( m_octets ), breath::cend( m_octets ),
                       breath::cbegin( other.m_octets )) ;
}

bool
uuid::less::operator()( uuid const & u1, uuid const & u2 ) const noexcept
{
    return std::lexicographical_compare( breath::cbegin( u1.m_octets ),
                                         breath::cend(   u1.m_octets ),
                                         breath::cbegin( u2.m_octets ),
                                         breath::cend(   u2.m_octets ) ) ;
}

std::ostream &
operator <<( std::ostream & original_stream, uuid const & uu )
{
    stream_equivalent< std::ostream >
                        equiv( original_stream ) ;
    std::ostream &      os = equiv.get() ;

    os.fill( '0' ) ;

    os.setf( std::ios_base::hex, std::ios_base::basefield ) ;
    os.setf( std::ios_base::right, std::ios_base::adjustfield ) ;
    os.unsetf( std::ios_base::showbase ) ;
    os.unsetf( std::ios_base::uppercase ) ;

    for ( int i = 0 ; i < 16 ; ++ i ) {
        os << std::setw( 2 ) <<
              static_cast< unsigned int >( uu.m_octets[ i ] ) ;

        if ( i == 3 || i == 5 || i == 7 || i == 9 ) {
            os << '-' ;
        }
    }
    return original_stream ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
