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
//!            operators (\c ==, \c !=, \c <, \c <=, \c >, \c >=) for a
//!            derived class.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_9eLHEHtKblEdQIGuXiqd2HmEUjrUscjf
#define BREATH_GUARD_9eLHEHtKblEdQIGuXiqd2HmEUjrUscjf

#include "breath/operator/equality_comparison.hpp"

namespace breath {
namespace adl_shield {

//      comparison:
//      ===========
//
//!     This is completely analogous to \c equality_comparison, but
//!     provides all six comparison operators (\c ==, \c !=, \c <, \c
//!     <=, \c >, \c >=).
//!
//!     In addition to %is_equal(), your class \C must provide a public
//!     const member function named \c compare which accepts a \c C
//!     argument \c other and returns:
//!
//!      - a value \c < \c 0 if \c *this is less than \c other
//!
//!      - a value \c == \c 0 if \c *this is equal to \c other
//!
//!      - a value \c > \c 0 if \c *this is greater than \c other
//!
//!     The return type doesn't need to be \c int: anything that is
//!     comparable to zero will work. Note that this would allow
//!     handling partial orderings, by returning, for incomparable
//!     pairs, a value for which none of \c == \c 0, \c < \c 0 and \c >
//!     \c 0 are true.
//!
//!     See the documentation of \c equality_comparison for more
//!     information, including ADL protection.
// ---------------------------------------------------------------------------
template< typename T >
class comparison
    :   private equality_comparison< T >
{
    // [FUTURE], [C++17], [gps]:
    //      These are all candidates for [[ nodiscard ]]
    friend bool         operator <( T const & lhs, T const & rhs )
    {
        return lhs.compare( rhs ) < 0 ;
    }

    friend bool         operator <=( T const & lhs, T const & rhs )
    {
        return lhs.compare( rhs ) <= 0 ;
    }

    friend bool         operator >( T const & lhs, T const & rhs )
    {
        return lhs.compare( rhs ) > 0 ;
    }

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

using adl_shield::comparison ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
