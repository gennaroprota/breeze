// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2015-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/process/set_current_directory.hpp"
#include "breeze/diagnostics/last_api_error.hpp"
#include "breeze/diagnostics/assert.hpp"
#include <Windows.h>

namespace breeze_ns {

void
set_current_directory( std::string const & dir )
{
    BREEZE_ASSERT( 0 < dir.length() && dir.length() < MAX_PATH ) ;

    //      TODO: use directory_separators()?
    // -----------------------------------------------------------------------
    BREEZE_ASSERT( dir.back() == '\\' || dir.back() == '/' ||
                   dir.length() <= ( MAX_PATH - 2 ) ) ;

    if ( SetCurrentDirectoryA( dir.c_str() ) == 0 ) {
        throw last_api_error( "SetCurrentDirectory() failed" ) ;
    }
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
