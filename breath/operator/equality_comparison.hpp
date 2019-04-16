// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Base class template to provide equality comparison
//!            operators.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_FVjQpxOUioJICCQIoTK5TmuA8UEe4UzI
#define BREATH_GUARD_FVjQpxOUioJICCQIoTK5TmuA8UEe4UzI

namespace breath {
namespace adl_shield {

//      equality_comparison:
//      ====================
//
//!     The class template \c equality_comparison provides <code>
//!     operator ==()</code> and <code>operator !=()</code> as namespace
//!     scope functions whose name is associated "on demand" (i.e. at
//!     instantiation) to class \c T, via ADL.
//!
//!     Usage:
//!     ------
//!
//!      - Provide an %is_equal() function for your class \c C.
//!
//!      - Add <code>equality_comparison< C ></code> as a private base
//!        class of \c C.
//!
//!     As a result, \c == and \c != will be available too for class \c
//!     C and defined in terms of is_equal().
//!
//!     ADL protection:
//!     ---------------
//!
//!     Even though this uses the Barton-Nackman idiom and relies on its
//!     standard-conforming, ADL-based, mechanics (no friend injection),
//!     it is protected from ADL in namespace \c breath in a way which
//!     allows only the provided operator functions to be found.
//!
//!     This means that the user can safely derive their own type from
//!     any of its instantiations \e without risk of ADL picking up
//!     anything \e unintended in \c namespace \c breath. Example:
//!
//!         Example TODO:
//!
//!     Naming rationale:
//!     -----------------
//!
//!     The name of the class template indicates the kind of comparison
//!     that its target will support. This leads to a noun-based name
//!     (as opposed, for instance, to "equality_comparable"),
//!     consistently with the general naming style of the Breath C++
//!     components.
// -------------------------------------------------------------------------
template< typename T >
class equality_comparison
{
    friend bool         operator ==( T const & lhs, T const & rhs)
    {
        return lhs.is_equal( rhs ) ;
    }
    friend bool         operator !=( T const & lhs, T const & rhs )
    {
        return !( lhs == rhs ) ;
    }

protected:
                        ~equality_comparison() noexcept = default ;
} ;

}

using breath::adl_shield::
                        equality_comparison ;
}


#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
