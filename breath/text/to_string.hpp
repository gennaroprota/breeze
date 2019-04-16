// ===========================================================================
//                        Copyright 2011 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Returns the textual representation of an object.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_JRFfcCLm3oqVulEWGOycMApryPN2pq33
#define BREATH_GUARD_JRFfcCLm3oqVulEWGOycMApryPN2pq33

#include <string>

namespace breath {

//      to_string():
//      ============
//
//!     \return
//!         The textual representation of its argument.
// -------------------------------------------------------------------------
template< typename OutputStreamable >
std::string         to_string( OutputStreamable const & ) ;

}

#include "brt/to_string.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
