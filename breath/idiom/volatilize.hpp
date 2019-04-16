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
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_4VpDkPMRFQlDZhFnubC67vt6hSC6EvrJ
#define BREATH_GUARD_4VpDkPMRFQlDZhFnubC67vt6hSC6EvrJ

namespace breath {

//!     Little helper to add \c volatile qualification to an lvalue
//!     expression without using \c static_cast (which might be too
//!     powerful) and without breaking the expression in two parts.
// -------------------------------------------------------------------------
template< typename T >
T volatile &
volatilize( T & ref )
{
    return ref ;
}

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
