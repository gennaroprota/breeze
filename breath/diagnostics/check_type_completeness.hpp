// ===========================================================================
//                     Copyright 2006-2007 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Checks that a type is complete at the point of
//!            instantiation.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_zosglTB4b62CILKxpxWmmQwQ28EfOH6T
#define BREATH_GUARD_zosglTB4b62CILKxpxWmmQwQ28EfOH6T

namespace breath {

//      check_type_completeness():
//      ==========================
//
//
//!     To be used to check that \c T is a complete type at the point
//!     of instantiation. If \c T is incomplete then the expression
//!
//!     \code
//!         check_type_completeness< T >()
//!     \endcode
//!
//!     renders the program \e ill-formed.
// ---------------------------------------------------------------------------
template< typename T >
void
check_type_completeness()
{
    static_cast< void >( sizeof( T ) ) ;
}

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
