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

#include <Windows.h>

#include <cstdint>

namespace breath {
namespace uuid_private {

int                 max_uuids_per_system_tick() ;
std::uint64_t       to_uint64( FILETIME const & ft ) ;
std::uint64_t       system_time_for_uuid() ;

//      I couldn't find any authoritative reference on the possible
//      resolutions of GetSystemTimeAsFileTime(), used below (note: keep
//      in sync!). So, let's be safe and only allow 1 UUID per tick.
// ---------------------------------------------------------------------------
int
max_uuids_per_system_tick()
{
    return 1 ;
}

std::uint64_t
to_uint64( FILETIME const & ft )
{
    int const           dword_bits = 32 ;
    return ( static_cast< std::uint64_t >( ft.dwHighDateTime ) << dword_bits ) |
           ft.dwLowDateTime ;
}

//      Note: keep in sync with max_uuids_per_system_tick().
// ---------------------------------------------------------------------------
std::uint64_t
system_time_for_uuid()
{
    //      NT keeps time in FILETIME format, which is 100ns ticks since
    //      Jan 1, 1601. UUIDs use time in 100ns ticks since Oct 15,
    //      1582. The difference is 17 days in Oct + 30 (Nov) + 31 (Dec)
    //      + 18 years and 5 leap days.
    // -----------------------------------------------------------------------
    FILETIME            ft ;
    GetSystemTimeAsFileTime( &ft ) ;
    return   to_uint64( ft ) +
             std::uint64_t( 1000 * 1000 * 10 )
           * std::uint64_t( 60 * 60 * 24 )
           * std::uint64_t( 17 + 30 + 31 + 365 * 18 + 5 ) ;
}

}
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
