// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2007-2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/environment/windows_only/get_operating_system_id.hpp"
#include "breeze/environment/windows_only/operating_system_id.hpp"
#include "breeze/environment/windows_only/windows_version_info.hpp"

#include <Windows.h>

namespace breeze_ns {
namespace           {

constexpr int
win_version( int major, int minor )
{
    return major * 256 + minor ;
}

bool
is_server_2003_r2()
{
    //      Define the sm_* constant ourselves, for now, to avoid
    //      requiring the latest SDK headers. [FUTURE]
    // -----------------------------------------------------------------------
    int const           sm_serverr2 = 89 ;
    return GetSystemMetrics( sm_serverr2 ) != 0 ;
}

operating_system_id
identify_nt( windows_version_info const & info )
{
    operating_system_id id = operating_system_id::windows_unknown ;
    int const           version =
                  win_version( info.major_version(), info.minor_version() ) ;

    if ( windows_version_info::is_client() ) {
        switch ( version ) {
        case win_version( 10, 0 ):
            id = operating_system_id::windows_10 ;
            break ;

        case win_version( 6, 3 ):
            id = operating_system_id::windows_8_1 ;
            break ;

        case win_version( 6, 2 ):
            id = operating_system_id::windows_8 ;
            break ;

        case win_version( 6, 1 ):
            id = operating_system_id::windows_7 ;
            break ;

        case win_version( 6, 0 ):
            id = operating_system_id::windows_vista ;
            break ;

        case win_version( 5, 2 ):
            if ( windows_version_info::is_64_bit() ) {
                id = operating_system_id::windows_xp_professional_x64_edition ;
            }
            break ;

        case win_version( 5, 1 ):
            id = operating_system_id::windows_xp ;
            break ;

        case win_version( 5, 0 ):
            id = operating_system_id::windows_2000 ;
            break ;

        default:
            // hmm... new version on the shelves?
            id = operating_system_id::windows_unknown ;
            break ;
        }
    } else {
        switch ( version ) {
        case win_version( 10, 0 ):
        {
            //      Build numbers taken from:
            //        <https://docs.microsoft.com/en-us/windows-server/get-started/windows-server-release-info>.
            //
            //      Unfortunately, not even this filth is enough to
            //      distinguish Server 2019 v.1809 from Server v.1809,
            //      because they have the same everything. What the
            //      heck, Microsoft.
            // ---------------------------------------------------------------
            int const           latest_2019   = 17763 ;
            int const           latest_2016   = 14393 ;
            if ( info.build_number() > latest_2019 ) {
                id = operating_system_id::windows_server ;
            } else if ( info.build_number() > latest_2016 ) {
                id = operating_system_id::windows_server_2019 ;
            } else {
                id = operating_system_id::windows_server_2016 ;
            }
            break ;
        }

        case win_version( 6, 3 ):
            id = operating_system_id::windows_server_2012_r2 ;
            break ;

        case win_version( 6, 2 ):
            id = operating_system_id::windows_server_2012 ;
            break ;

        case win_version( 6, 1 ):
            id = operating_system_id::windows_server_2008_r2 ;
            break ;

        case win_version( 6, 0 ):
            id = operating_system_id::windows_server_2008 ;
            break ;

        case win_version( 5, 2 ):
            // gps TODO: how to distinguish Windows Storage Server 2003?
            id = is_server_2003_r2()
                ? operating_system_id::windows_server_2003_r2
                : operating_system_id::windows_server_2003
                ;
            break ;

        case win_version( 5, 0 ):
            id = operating_system_id::windows_2000 ;
            break ;

        default:
            // hmm... new version on the shelves?
            id = operating_system_id::windows_unknown ;
            break ;
        }
    }

    return id ;
}

}

operating_system_id
get_operating_system_id()
{
    windows_version_info const
                        info ;

    //      When Windows 9x was supported as well, the function
    //      identify_nt() was accompanied by a corresponding
    //      identify_9x(). Now that the latter has disappeared,
    //      identify_nt() could be incorporated directly into
    //      get_operating_system_id().
    // -----------------------------------------------------------------------
    return identify_nt( info ) ;
}

}
