// ===========================================================================
//                     Copyright 2007-2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Returns the `operating_system_id` of the running
//!            operating system (Windows only).
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_lc9dZp5eUrNd9dbNZHDcvW36RGyTlJ77
#define BREEZE_GUARD_lc9dZp5eUrNd9dbNZHDcvW36RGyTlJ77

#include "breeze/top_level_namespace.hpp"
#include "breeze/environment/windows_only/operating_system_id.hpp"

namespace breeze_ns {

//      get_operating_system_id():
//      ==========================
//
//!     \copybrief get_operating_system_id.hpp
//!
//!     This "determines" the running OS based on information returned
//!     by Windows itself: initially the implementation used
//!     `GetVersionEx()`, which "lies" when the executable runs in
//!     compatibility mode; now it uses an API which doesn't appear to
//!     be affected by the compatibility settings, so we should detect
//!     the "true" OS, anyway.
// -----------------------------------------------------------------------
operating_system_id get_operating_system_id() ;

}

#endif
