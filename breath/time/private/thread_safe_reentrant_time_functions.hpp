// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#ifndef BREATH_GUARD_krhKqbhdeRKtskiukvWAb1Ax6cnwgQ77
#define BREATH_GUARD_krhKqbhdeRKtskiukvWAb1Ax6cnwgQ77

#include <time.h>

namespace breath {

//! \cond
namespace time_private {

//      TODO: decide where to put these declarations.
// ---------------------------------------------------------------------------
tm const *          thread_safe_reentrant_gmtime(    time_t const * time,
                                                     tm * result ) ;
tm const *          thread_safe_reentrant_localtime( time_t const * time,
                                                     tm * result ) ;

}
//! \endcond

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
