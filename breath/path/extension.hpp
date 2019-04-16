// ===========================================================================
//                     Copyright 2006-2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Returns the file name extension from a given path.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_BtNGaSvg9IBya5J9FQZmayMQRBx2oBwo
#define BREATH_GUARD_BtNGaSvg9IBya5J9FQZmayMQRBx2oBwo

#include <string>

namespace breath {

//      extension():
//      ============
//
//!     \return
//!         The extension of the file name part of \c path, including
//!         the period, if any. This is the substring starting from the
//!         last period, except that:
//!
//!          - if the file name part is "." or ".." (without quotes) or
//!            does not contain a period, the result is an empty string;
//!
//!          - if the file name part begins with a period, then that
//!            initial period (and only that) is ignored (so ".dotfile"
//!            gives "", while ".dotfile.txt" gives ".txt").
//!
//!     \note
//!         This behavior is aligned with that of <code>
//!         std::filesystem::path::extension()</code> (C++17).
// ---------------------------------------------------------------------------
std::string         extension( std::string const & path ) ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
