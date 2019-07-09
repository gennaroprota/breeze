// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include <sys/time.h>

#include <cstdint>

namespace breath {
namespace uuid_private {

std::uint64_t       system_time_for_uuid() ;

std::uint64_t
system_time_for_uuid()
{
    //      gettimeofday() returns the time in seconds and microseconds
    //      since the UNIX epoch, i.e. January 1, 1970.
    //
    //      UUIDs use time in 100ns ticks since Oct 15, 1582.
    //
    //      TODO: verify the hex constant, which we took from RFC 4122.
    // -----------------------------------------------------------------------
    timeval             tv ;
    gettimeofday( &tv, nullptr ) ;

    return   std::uint64_t( tv.tv_sec  ) * 10 * 1000 * 1000
           + std::uint64_t( tv.tv_usec ) * 10
           + 0x01B21DD213814000 ;
}

}
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
