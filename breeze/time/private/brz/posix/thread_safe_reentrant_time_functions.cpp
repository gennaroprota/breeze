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

#include <time.h>

namespace breeze_ns {
namespace time_private {

tm const *
thread_safe_reentrant_gmtime( time_t const * time, tm * result )
{
    return gmtime_r( time, result ) ;
}

tm const *
thread_safe_reentrant_localtime( time_t const * time, tm * result )
{
    return localtime_r( time, result ) ;
}

}
}
