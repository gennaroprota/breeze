// ===========================================================================
//                     Copyright 2006-2010 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Named constants for program termination codes.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_jUGeAMeGfcMWbQ12OyJckoIpy0CYCBq0
#define BREEZE_GUARD_jUGeAMeGfcMWbQ12OyJckoIpy0CYCBq0

#include "breeze/top_level_namespace.hpp"
#include "breeze/porting/dependent_source.hpp"

#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wunused-const-variable"

namespace breeze_ns {

//      This can be specified portably, so we define it outside of the
//      system_family-dependent exit_code.ipp's.
// ---------------------------------------------------------------------------
static int const    exit_success = 0 ;

}

#include BREEZE_DEPENDENT_SOURCE( system_family, exit_code.ipp )
#pragma GCC diagnostic pop
#endif
