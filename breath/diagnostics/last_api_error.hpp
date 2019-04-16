// ===========================================================================
//                        Copyright 2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief The last error from the OS API.
// ---------------------------------------------------------------------------
//!
//!     An exception class representing the last error encountered
//!     in an OS API call. It corresponds to \c GetLastError() under
//!     Windows and \c errno under Unix.
//!
//!     The idea is that after an unsuccessful API call you write:
//!     <code>
//!         throw last_api_error( "<APIName>() failed" ) ;
//!     </code>
//!     and you're done with error handling.
//!
//!     The class is OutputStreamable, so you can also use
//!     \c breath::as_string(), which gives more information than the
//!     member \c what(), but may throw.
// ---------------------------------------------------------------------------

#include "breath/diagnostics/private/last_api_error.hpp"

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
