// ===========================================================================
//                     Copyright 2006-2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Compile-time selection between types.
//!
//!     In C++11 and later, this is superseded by `std::conditional` but
//!     we need it in some C++03 projects.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_Mcff5zkaJE9eTbXnwJQWQ2WlCXIXfcmc
#define BREEZE_GUARD_Mcff5zkaJE9eTbXnwJQWQ2WlCXIXfcmc

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//!     \brief
//!         Like `select`, but with the condition represented as a
//!         `bool` value, not a type.
// ---------------------------------------------------------------------------
template< bool condition, typename T, typename U >
class select_
{
public:
    //!     A typedef for the type `T`.
    // -----------------------------------------------------------------------
    typedef T           type ;

    //!     A typedef for `select_< ! condition, T, U >`.
    // -----------------------------------------------------------------------
    typedef select_< ! condition, T, U >
                        opposite ;
} ;

//!\cond implementation
//!
template< typename T, typename U >
class select_< false, T, U >
{
public:
    //!     A typedef for the type `U`.
    // -----------------------------------------------------------------------
    typedef U           type ;

    //!     A typedef for `select_< true, T, U >`.
    typedef select_< true, T, U >
                        opposite ;
} ;
//!\endcond


//!     \copybrief select.hpp
// ---------------------------------------------------------------------------
template< typename Cond, typename T, typename U >
class select
{
public:
    //!     The result of the metafunction.
    // -----------------------------------------------------------------------
    typedef typename select_< Cond::value, T, U >::type
                        type ;
} ;

}

#endif
