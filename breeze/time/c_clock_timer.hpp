// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A timer based on \c std::clock().
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_u43dOQ8kSA0wS32RQRLI7UM66PBoXLSA
#define BREEZE_GUARD_u43dOQ8kSA0wS32RQRLI7UM66PBoXLSA

#include "breeze/top_level_namespace.hpp"
#include "breeze/time/timer.hpp"
#include "breeze/time/c_clock_policy.hpp"

namespace breeze_ns {

typedef timer< c_clock_policy >
                    c_clock_timer ;

}

#endif
