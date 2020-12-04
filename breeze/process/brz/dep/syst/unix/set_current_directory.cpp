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
#include <unistd.h>
#include <string>

namespace breeze_ns {

void
set_current_directory( std::string const & dir )
{
    int const           r = chdir( dir.c_str() ) ;
    if ( r == -1 ) {
        throw last_api_error( "chdir() failed" ) ;
    }
}

}
