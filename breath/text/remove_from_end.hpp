// ===========================================================================
//                        Copyright 2013 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Removes a \c std::string from the end of another one.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_vf6LuqjTQ9wAJWXZsNnALWlVf4PYtieN
#define BREATH_GUARD_vf6LuqjTQ9wAJWXZsNnALWlVf4PYtieN

#include <string>

namespace breath {

//!     \return
//!         If \c str ends with \c to_be_removed, \c str with the
//!         \c to_be_removed part erased from its end; otherwise
//!         a copy of \c str.
// -------------------------------------------------------------------------
std::string         remove_from_end( std::string const & str,
                                     std::string const & to_be_removed ) ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
