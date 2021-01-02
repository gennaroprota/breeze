// ===========================================================================
//                     Copyright 2006-2007 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Adds a \c volatile qualification.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_4VpDkPMRFQlDZhFnubC67vt6hSC6EvrJ
#define BREEZE_GUARD_4VpDkPMRFQlDZhFnubC67vt6hSC6EvrJ

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//      volatilize():
//      =============
//
//!     Adds a \c volatile qualification to an lvalue expression.
//!
//!     This allows avoiding using a \c const_cast or a \c static_cast,
//!     or introducing an additional variable.
//!
//!     \return
//!         ref
// ---------------------------------------------------------------------------
template< typename T >
T volatile &
volatilize( T & ref )
{
    return ref ;
}

}

#endif
