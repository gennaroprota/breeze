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
//
//      get_os():
//      =========
//
//      Windows-specific implementation.
//
//      November 2016 note:
//      -------------------
//
//      what follows in the "Necessary background" section is the
//      analysis done when the implementation used GetVersionEx().
//      However that API has changed semantics in Windows 8.1 and
//      can no longer be used to identify the running system.
//      The current implementation uses a different approach, so the
//      following has just historical value.
//      Also, the minimum supported Windows version is now Windows
//      2000.
// ---------------------------------------------------------------------------
//
//      Necessary background:
//      ---------------------
//
//      The bizarre design and "evolution" of the Windows API makes
//      the whole task of getting the running OS version a fastidious
//      programming puzzle, and an accurate analysis is in order
//      before attempting a reusable implementation. First, two API
//      functions exist for the purpose: GetVersion() and
//      GetVersionEx(), with the latter being available (as of April
//      2007, and presumably ever) on all Windows flavors except NT
//      3.1. Given the current low diffusion of this latter Windows we
//      give up its support and always use GetVersionEx().
//
//      From now on, we assume that you have read the documentation of
//      GetVersionEx(), OSVERSIONINFO and OSVERSIONINFOEX. You have
//      likely immediately noticed from the MS docs, that different
//      Windows versions exist sharing the same version number:
//
//      Operating system               Version number
//
//       Windows Server "Longhorn"      6.0
//       Windows Vista                  6.0
//
//       Windows XP Professional x64    5.2
//       Windows Server 2003 R2         5.2
//       Windows Server 2003            5.2
//
//       Windows XP                     5.1
//       Windows 2000                   5.0
//
// ---------------------------------------------------------------------------
//      Here's a simple tree-like diagram deducible from the
//      OSVERSIONINFOEX documentation:
//
// major              4                        5                      6
//             /    /    \    \            /   |   \                  |
// minor      0    10    90    \          0    1    2                 0
//           .   Win98  WinMe  ...       ...  XP   XP Pro x64       Vista
//                                                 or 2003 R2    or "Longhorn"
//           |\                                    or 2003
// Platf.    | \                          -
//  Id      WIN NT                      PLAT_NT
//          |   |
//          95  NT 4.0                  2000 ??????? po' esse NT??? (gps)
//
//                                                              [ Diagram 1 ]
// ---------------------------------------------------------------------------
//
//      Note that, not only the pair (major, minor) isn't sufficient
//      to determine what OS is running---which we already knew---but,
//      even adding dwPlatformId, indecisions remain (5.2 and 6.0
//      branches).
//
//      In effect, not even *all* the members of OSVERSIONINFOEX are
//      (always) enough: we need, depending on the case, either
//      wProductType, member of OSVERSIONINFOEX, or a call to
//      GetSystemMetrics [sic] or a call to GetSystemInfo, as
//      sketched in pseudo-code below:
//
//         // not supported (yet)
//         if version > 6.0
//             [FUTURE]
//
//         // Vista / Server "Longhorn"
//         if version == 6.0
//             if wProductType == VER_NT_WORKSTATION
//                 "Windows Vista"
//             else
//                 "Windows Server \"Longhorn\""
//
//         // XP Professional x64 Edition / Server 2003 R2 / Server 2003
//         if version == 5.2
//             if GetSystemInfo() == x64 and wProductType == NT_WORKSTATION
//                 "Windows XP Professional x64 Edition"
//             else if ( GetSystemMetrics( SM_SERVERR2 ) ) != 0
//                 "Windows Server 2003 R2"
//             else
//                 "Windows Server 2003"
//
//         else
//             // see [ Diagram 1 ]
//             5.1      XP
//             5.0      2000
//             ...      ...
//
//
// ===========================================================================
//
// Once you have figured out the version of the operating system that is
// running, you can attack the details:
//
//    Detected OS        95      98                  Me            All others
//    CSDVersion        " C"    " A"                 ??
//                      OSR2   Second Edition   additional info   service pack
// ---------------------------------------------------------------------------
//
// Further details can be gathered by examining the wSuiteMask member of
// the OSVERSIONEX info structure (not available on...) and/or querying specific
// registry values. This is basically all trivial switch-case like stuff and
// doesn't really need a diagram.
//
//                          NT 4                        2000        XP      2003
//    SuiteMask
// (   only in
// OSVERSIONINFOEX )          1            3                    PERSONAL    DATACENTER
//                                                                      [*]
//                        Workstation   Server                   |Home Ed.|   dc
//
// (note the initial space in " C" and " A")
//
// [*] Server 2003 editions:
//      switch( SuiteMask )
//        case DATACENTER: "Datacenter Edition" break ;
//        case ENTERPRISE: "Enterprise Edition" break ;
//        case BLADE:      "Web Edition"        break ;
//        default:         "Standard Edition"   break ;
//
// Limitations:
//  For simplicity's sake, we avoid the following detections:
//
//    * Specific edition for Windows NT 4.0 SP6 and later
//      (NT Workstation: Workstation, Home Edition, Professional)
//      (NT Server:      Datacenter Edition, Enterprise Edition, Web Edition, Standard Edition)

#include "breath/environment/windows_only/get_os.hpp"
#include "breath/environment/windows_only/os_id.hpp"
#include "breath/environment/windows_only/windows_version_info.hpp"

#include <Windows.h>

namespace breath_ns {
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

os_id
identify_nt( windows_version_info const & info )
{
    os_id               id( os_id::windows_unknown ) ;
    int const           version(
                  win_version( info.major_version(), info.minor_version() ) ) ;

    if ( windows_version_info::is_client() ) {
        switch ( version )
        {
        case win_version( 10, 0 ):
            id = os_id::windows_10 ;
            break ;

        case win_version( 6, 3 ):
            id = os_id::windows_8_1 ;
            break ;

        case win_version( 6, 2 ):
            id = os_id::windows_8 ;
            break ;

        case win_version( 6, 1 ):
                id = os_id::windows_7 ;
            break ;

        case win_version( 6, 0 ):
                id = os_id::windows_vista ;
            break ;

        case win_version( 5, 2 ):
            if ( windows_version_info::is_64_bit() ) {
                id = os_id::windows_xp_professional_x64_edition ;
            }
            break ;

        case win_version( 5, 1 ):
            id = os_id::windows_xp ;
            break ;

        case win_version( 5, 0 ):
            id = os_id::windows_2000 ;
            break ;

        default:
            // hmm... new version on the shelves?
            id = os_id::windows_unknown ;
            break ;
        }
    } else {
        switch ( version )
        {
        case win_version( 10, 0 ):
            id = os_id::windows_server_2016 ;
            break ;

        case win_version( 6, 3 ):
            id = os_id::windows_server_2012_r2 ;
            break ;

        case win_version( 6, 2 ):
            id = os_id::windows_server_2012 ;
            break ;

        case win_version( 6, 1 ):
                id = os_id::windows_server_2008_r2 ;
            break ;

        case win_version( 6, 0 ):
                id = os_id::windows_server_2008 ;
            break ;

        case win_version( 5, 2 ):
            // gps TODO: how to distinguish Windows Storage Server 2003?
                id = is_server_2003_r2()
                    ? os_id::windows_server_2003_r2
                    : os_id::windows_server_2003
                    ;
            break ;

        case win_version( 5, 0 ):
            id = os_id::windows_2000 ;
            break ;

        default:
            // hmm... new version on the shelves?
            id = os_id::windows_unknown ;
            break ;
        }
    }

    return id ;
}

}

os_id
get_os()
{
    windows_version_info const
                        info ;

    //      When Windows 9x was supported as well, the function
    //      identify_nt() was accompanied by a corresponding
    //      identify_9x(). Now that the latter has disappeared,
    //      identify_nt() could be incorporated directly into get_os().
    // -----------------------------------------------------------------------
    return identify_nt( info ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
