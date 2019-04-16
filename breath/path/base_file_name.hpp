// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Returns the file name part of a path.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_t4h0OWeS8sua5gWE50YSmGUx15Kw2wrR
#define BREATH_GUARD_t4h0OWeS8sua5gWE50YSmGUx15Kw2wrR

#include <string>

namespace breath {

//      base_file_name():
//      =================
//
//!     \return
//!         The file name part of a path. Assumes that the path is
//!         well-formed.
// -------------------------------------------------------------------------
std::string         base_file_name( std::string const & full_path ) ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
