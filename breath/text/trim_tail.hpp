// ===========================================================================
//                     Copyright 2008-2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A \c std::string trimmer (tail of string).
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_rAf6FomrfEupsrKlsZvh9xwbNaeg8pxp
#define BREATH_GUARD_rAf6FomrfEupsrKlsZvh9xwbNaeg8pxp

#include <string>

namespace breath {

class               set_of_chars ;

std::string         trim_tail( std::string const & str ) ;

std::string         trim_tail( std::string const &  str,
                               set_of_chars const & to_remove ) ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
