// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Metafunction to get the corresponding unqualified type of
//!            its argument.
//!
//!     Example: <code>unqualify< char const >::type == char</code>
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_y2qhOILUvLqZ79ED32KSdlOabmhuefgQ
#define BREATH_GUARD_y2qhOILUvLqZ79ED32KSdlOabmhuefgQ

// NOTE:
//      No #includes here.
//
//      This is a very basic facility, used by many other components
//      of the meta subsystem; do not introduce dependencies (they are
//      not logically necessary: the C++ template system has all that
//      is needed to implement the functionality).

namespace breath {
namespace meta {

//      unqualify:
//      ==========
//
//!     Gives the corresponding unqualified type of its argument.
// ---------------------------------------------------------------------------
template< typename T >
class unqualify
{
public:
    //!     A typedef for the type \c T.
    // -----------------------------------------------------------------------
    typedef T type ;
} ;

//! \cond implementation
template< typename T >
class unqualify< T const >
{
public:
    //!     A typedef for the type \c T.
    // -----------------------------------------------------------------------
    typedef T type ;
} ;

template< typename T >
class unqualify< T volatile >
{
public:
    //!     A typedef for the type \c T.
    // -----------------------------------------------------------------------
    typedef T type ;
} ;

template< typename T >
class unqualify< T volatile const >
{
public:
    //!     A typedef for the type \c T.
    // -----------------------------------------------------------------------
    typedef T type ;
} ;
//! \endcond
}
}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
