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
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_y2qhOILUvLqZ79ED32KSdlOabmhuefgQ
#define BREEZE_GUARD_y2qhOILUvLqZ79ED32KSdlOabmhuefgQ

// NOTE:
//      No #includes here, except the one to define the namespace name.
//
//      This is a very basic facility, potentially used by many
//      meta-programming components in a code base; do not introduce
//      dependencies (they are not logically necessary: the C++ template
//      system has all that is needed to implement the functionality).
// ---------------------------------------------------------------------------
#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//      unqualify:
//      ==========
//
//!     \copybrief unqualify.hpp
//!
//!     Example: `unqualify< char const >::type` is `char`.
// ---------------------------------------------------------------------------
template< typename T >
class unqualify
{
public:
    //!     A typedef for the type `T`.
    // -----------------------------------------------------------------------
    typedef T           type ;
} ;

//!\cond implementation
template< typename T >
class unqualify< T const >
{
public:
    //!     A typedef for the type `T`.
    // -----------------------------------------------------------------------
    typedef T           type ;
} ;

template< typename T >
class unqualify< T volatile >
{
public:
    //!     A typedef for the type `T`.
    // -----------------------------------------------------------------------
    typedef T           type ;
} ;

template< typename T >
class unqualify< T volatile const >
{
public:
    //!     A typedef for the type `T`.
    // -----------------------------------------------------------------------
    typedef T           type ;
} ;
//!\endcond
}

#endif
