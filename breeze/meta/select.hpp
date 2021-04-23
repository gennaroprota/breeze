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

//!     \copybrief select.hpp
// ---------------------------------------------------------------------------
template< bool condition, typename T, typename U >
class select
{
public:
    //!     A typedef for the type `T`.
    // -----------------------------------------------------------------------
    typedef T           type ;

    //!     A typedef for `select< ! condition, T, U >`.
    // -----------------------------------------------------------------------
    typedef select< ! condition, T, U >
                        opposite ;
} ;

//!\cond implementation
//!
template< typename T, typename U >
class select< false, T, U >
{
public:
    //!     A typedef for the type `U`.
    // -----------------------------------------------------------------------
    typedef U           type ;

    //!     A typedef for `select< true, T, U >`.
    typedef select< true, T, U >
                        opposite ;
} ;
//!\endcond

}

#endif
