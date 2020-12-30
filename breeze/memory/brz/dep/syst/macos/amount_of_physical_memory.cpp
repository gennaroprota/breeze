// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/memory/amount_of_physical_memory.hpp"
#include "breeze/diagnostics/last_api_error.hpp"
#include <sys/types.h>
#include <sys/sysctl.h>

namespace breeze_ns {

//      As of December 31, 2020, we cannot use the generic Unix
//      implementation for amount_of_physical_memory(), under Mac OS X
//      10.15.7 (used by GitHub Actions), because the Mac headers do not
//      define _SC_PHYS_PAGES.
// ---------------------------------------------------------------------------
long long
amount_of_physical_memory()
{
    long long           result ;
    size_t              size = sizeof result ;
    int const           ret =
        sysctlbyname( "hw.memsize", &result, &size, nullptr, 0 ) ;
    if ( ret != 0 ) {
        throw last_api_error( "sysctlbyname( \"hw.memsize\"... ) failed " ) ;
    }

    return result / 1024 ;
}

}
