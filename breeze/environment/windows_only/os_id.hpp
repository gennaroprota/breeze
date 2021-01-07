// ===========================================================================
//                     Copyright 2007-2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Operating system identifier for Windows.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_y14wSYOBPQ4ReQuQzkBRjijvOvqDhYc7
#define BREEZE_GUARD_y14wSYOBPQ4ReQuQzkBRjijvOvqDhYc7

#include "breeze/top_level_namespace.hpp"
#include <iosfwd>

namespace breeze_ns {

//      os_id:
//      ======
//
//!     \copybrief os_id.hpp
//!
//!     A scoped enumeration to distinguish the various Windows
//!     versions.
// ---------------------------------------------------------------------------
//
//      Rationale for the deletion of the relational operators:
//
//      in my first idea of this class, it was my intent to support
//      inequality comparisons:
//
//        // windows 2000 or "later"?
//        if ( id >= os_id::windows_2000 )
//
//      And the constants, in fact, appear in oldest-to-newest order.
//      But...
//      I don't like too much the idea of having something which only
//      makes sense for one of the supported OSes, and perhaps not
//      even for it, in the future: right now, Windows versions seem
//      to have an established total ordering, but what about the
//      future? Microsoft seems on the way of "parallelizing" their
//      OS products over a "client line" (Windows XP etc.) and a
//      "server line" (Windows Server 2003 etc.); in the future it
//      seems to me they could well release two Windows variants of
//      which neither is "higher" or "lower" than the other.
// ---------------------------------------------------------------------------
enum class os_id
{
    //      Attention: keep in sync with the array definition in the
    //      .cpp file (used for stream insertion).
    //
    //      * windows_xp_professional_x64_edition is the only case where
    //      the word "edition" appears directly as a part of the OS
    //      name, rather than in the edition name (as in "Web Edition",
    //      "Home Edition" etc.) -- what should we do? leave "edition"
    //      or not?
    // ---------------------------------------------------------------------------
    windows_unknown,

    windows_2000,
    windows_xp,
    windows_server_2003,
    windows_home_server,
    windows_storage_server_2003,
    windows_server_2003_r2,
    windows_xp_professional_x64_edition,  // gps leave "edition"?
    windows_vista,
    windows_server_2008,
    windows_server_2008_r2,
    windows_7,
    windows_8,
    windows_server_2012,
    windows_8_1,
    windows_server_2012_r2,
    windows_10,
    windows_server_2016
} ;

std::ostream &      operator <<( std::ostream &, os_id ) ;

bool                operator <(  os_id, os_id ) = delete ;
bool                operator <=( os_id, os_id ) = delete ;
bool                operator >(  os_id, os_id ) = delete ;
bool                operator >=( os_id, os_id ) = delete ;

}

#endif
