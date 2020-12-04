// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#ifndef BREEZE_GUARD_krhKqbhdeRKtskiukvWAb1Ax6cnwgQ77
#define BREEZE_GUARD_krhKqbhdeRKtskiukvWAb1Ax6cnwgQ77

#include "breeze/top_level_namespace.hpp"
#include <time.h>

namespace breeze_ns {

//!\cond implementation
namespace time_private {

//      TODO: decide where to put these declarations.
// ---------------------------------------------------------------------------
tm const *          thread_safe_reentrant_gmtime(    time_t const * time,
                                                     tm * result ) ;
tm const *          thread_safe_reentrant_localtime( time_t const * time,
                                                     tm * result ) ;

}
//!\endcond

}

#endif
