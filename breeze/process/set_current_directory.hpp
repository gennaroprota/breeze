// ===========================================================================
//                        Copyright 2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Sets the current directory of the calling process.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_E6f26R6Om6D3dxAUPssS2yROHiV0L8sv
#define BREEZE_GUARD_E6f26R6Om6D3dxAUPssS2yROHiV0L8sv

#include "breeze/top_level_namespace.hpp"
#include <string>

namespace breeze_ns {

//      set_current_directory():
//      ========================
//
//!     Sets the current directory of the calling process to `dir`;
//!     `dir` must be a valid directory path.
//!
//!     \par Exceptions
//!         A `std::runtime_error` (which may be a `last_api_error`) if
//!         it fails.
// ---------------------------------------------------------------------------
void                set_current_directory( std::string const & dir ) ;

}

#endif
