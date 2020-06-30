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

#ifndef BREATH_GUARD_jUGeAMeGfcMWbQ12OyJckoIpy0CYCBq0
#define BREATH_GUARD_jUGeAMeGfcMWbQ12OyJckoIpy0CYCBq0

#include "breath/top_level_namespace.hpp"

namespace breath_ns {

extern int const    exit_success ;
extern int const    exit_failure ;

//      Maintenance note:
//          keep in sync with *all* the .cpp files of the various code
//          variants (brt/dep/ subdirectory).
//   -------------------------------------------------------------------------
extern int const    exit_warning ;
extern int const    exit_error ;
extern int const    exit_fatal ;
extern int const    exit_internal ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
