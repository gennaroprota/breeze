// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Base class template to provide equality and relational
//!            operators (`==`, `!=`, `<`, `<=`, `>`, `>=`) for a
//!            derived class.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_9eLHEHtKblEdQIGuXiqd2HmEUjrUscjf
#define BREEZE_GUARD_9eLHEHtKblEdQIGuXiqd2HmEUjrUscjf

#include "breeze/top_level_namespace.hpp"
#include "breeze/operator/equality_comparison.hpp"

namespace breeze_ns {
namespace adl_shield {

//      comparison:
//      ===========
//
//!     \copybrief comparison.hpp
//!
//!     This is completely analogous to `equality_comparison`, but
//!     provides all six comparison operators (`==`, `!=`, `<`, `<=`,
//!     `>`, `>=`).
//!
//!     In addition to %is_equal(), your class `C` must provide a public
//!     const member function named `compare` which accepts a `C`
//!     argument `other` and returns:
//!
//!      - a value `< 0` if `*this` is less than `other`
//!
//!      - a value `== 0` if `*this` is equal to `other`
//!
//!      - a value `> 0` if `*this` is greater than `other`
//!
//!     The return type doesn't need to be `int`: anything that is
//!     comparable to zero will work. Note that this would allow
//!     handling partial orderings, by returning, for incomparable
//!     pairs, a value for which none of `== 0`, `< 0` and `> 0` are
//!     true.
//!
//!     See the documentation of `equality_comparison` for more
//!     information, including ADL protection.
// ---------------------------------------------------------------------------
template< typename T >
class comparison
    :   private equality_comparison< T >
{
    //!     \return
    //!         lhs.compare( rhs ) < 0
    // -----------------------------------------------------------------------
    [[ nodiscard ]]
    friend bool         operator <( T const & lhs, T const & rhs )
    {
        return lhs.compare( rhs ) < 0 ;
    }

    //!     \return
    //!         lhs.compare( rhs ) <= 0 ;
    // -----------------------------------------------------------------------
    [[ nodiscard ]]
    friend bool         operator <=( T const & lhs, T const & rhs )
    {
        return lhs.compare( rhs ) <= 0 ;
    }

    //!     \return
    //!         lhs.compare( rhs ) > 0 ;
    // -----------------------------------------------------------------------
    [[ nodiscard ]]
    friend bool         operator >( T const & lhs, T const & rhs )
    {
        return lhs.compare( rhs ) > 0 ;
    }

    //!     \return
    //!         lhs.compare( rhs ) >= 0 ;
    // -----------------------------------------------------------------------
    [[ nodiscard ]]
    friend bool         operator >=( T const & lhs, T const & rhs )
    {
        return lhs.compare( rhs ) >= 0 ;
    }

protected:
    //!     Protected constructor, to enforce the usage as a base.
    //!
    //!     This used to be a protected destructor, but if a
    //!     user-declared destructor---even a defaulted one---exists,
    //!     the generation of a copy constructor is deprecated. Thus, we
    //!     switched to use a constructor, instead.
    // -----------------------------------------------------------------------
                        comparison() noexcept = default ;
} ;

}

using breeze::adl_shield::
                    comparison ;

}

#endif
