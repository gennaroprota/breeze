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

namespace breath {
namespace time_private {

//!     Microsoft's library doesn't provide gmtime_r(). Their gmtime(),
//!     though, uses a different tm struct for each thread, so it is
//!     thread-safe. But its not reentrant. To have both properties, we
//!     use gmtime_s(); note that this is a Microsoft-specific function
//!     that differs in two ways from the homonym C11 function:
//!
//!      a) the order of the parameters is the opposite
//!
//!      b) the return type is different
// ---------------------------------------------------------------------------
tm const *
thread_safe_reentrant_gmtime( time_t const * time, tm * result )
{
    errno_t const       e = gmtime_s( result, time ) ;

    return e != 0
               ? result
               : nullptr
               ;
}

//!     Likewise for localtime_r().
// ---------------------------------------------------------------------------
tm const *
thread_safe_reentrant_localtime( time_t const * time, tm * result )
{
    errno_t const       e = localtime_s( result, time ) ;

    return e != 0
               ? result
               : nullptr
               ;
}

}
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
