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

#ifndef BREATH_GUARD_u43dOQ8kSA0wS32RQRLI7UM66PBoXLSA
#define BREATH_GUARD_u43dOQ8kSA0wS32RQRLI7UM66PBoXLSA

#include "breath/time/elapsed_timer.hpp"
#include "breath/time/c_clock_device.hpp"

namespace breath {

typedef elapsed_timer< c_clock_device >
                    c_clock_timer ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
