// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Base class template to provide inequality comparison
//!            operators.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_9eLHEHtKblEdQIGuXiqd2HmEUjrUscjf
#define BREATH_GUARD_9eLHEHtKblEdQIGuXiqd2HmEUjrUscjf

#include "breath/operator/equality_comparison.hpp"

namespace breath {

namespace adl_shield {

//      comparison:
//      ===========
//
//!     This is completely analogous to equality_comparison. See the
//!     documentation of that facility for more information. The only
//!     difference is that you class \c C must provide a \c compare()
//!     member function, which accepts a \c C argument \c rhs to compare
//!     with \c *this, and returns a value \c < \c 0, \c == \c 0 or \c >
//!     \c 0 if \c *this is respectively less than \c rhs, equal to \c
//!     rhs or greater then rhs.
// ---------------------------------------------------------------------------
template< typename T >
class comparison
    :   private equality_comparison< T >
{
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
                        ~comparison() noexcept = default ;
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
