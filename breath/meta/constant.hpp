// =========================================================================
//                    Copyright 2006-2007 Gennaro Prota
//
//                 Licensed under the BSD 3-Clause License.
//            (See accompanying file BSD_3_CLAUSE_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>)
// _________________________________________________________________________
//
//!     \file
//!     \brief Wrapper for (integral) constant expressions.
// -------------------------------------------------------------------------
//
#ifndef BREATH_GUARD_agSZ9lxbOGpOtPA3Qy3JqLm28BJW8oRr
#define BREATH_GUARD_agSZ9lxbOGpOtPA3Qy3JqLm28BJW8oRr

#include "breath/meta/unqualify.hpp"

namespace breath {
namespace meta {

//! This template is a fundamental building block for meta-programming.
//! Among other things, it accomplishes three goals:
//!     - wrapping a constant into a type, as needed for compile time
//!       polymorphism
//!     - automatically generating a definition for the constant, if needed
//!       (see core issue 454)
//!     - when a definition is generated, making the constant a singleton,
//!       mapping every pair (type, value) to unique storage
//!
//! \typereq
//!     \a T must be a type suitable for declaring an integral constant
//!     expression or a cv-qualified version of such a type (e.g. <code>
//!     int volatile const </code>)
//!
//! \par Naming rationale
//!     though at the time of writing (September 2006) only constants
//!     of integral and enumeration type are allowed in C++, we chose
//!     a name which doesn't mention either families of types, in order
//!     to eventually accommodate, for instance, floating point types
//!     as well, if ever allowed by the standard
//!
//! \credit
//!     The basic idea of this class template was suggested by
//!     Paul Mensonides as <code>map_integral<></code>.
//!
template< typename T, T v >
class constant
{
private:
    typedef typename unqualify< T >::type unqualified_type ;
public:
    typedef unqualified_type
                        value_type ;
    typedef constant    type ;

    static value_type const
                        value = v ;
} ;

template< typename T, T v >
typename constant< T, v >::value_type const
constant< T, v >::value ;

}
}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
