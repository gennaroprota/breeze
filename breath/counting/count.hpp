// ===========================================================================
//                        Copyright 2007 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Arrays and containers element counter.
//!
//!     An extension of \c container::size() to cover both standard
//!     containers and built-in arrays.
//!
//!     The syntax is, uniformly, \c breath::count( a ) regardless of
//!     the actual type of \c a. See also begin_end.hpp.
//!
//!     These functions are made obsolete in C++17 by the namespace
//!     scope std::size()'s. However our version uses, for containers,
//!     a conditional noexcept that the standard version is not
//!     required to have.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_ivBlyIgMoh0KJl1p5J44xFCWiI9nPqRi
#define BREATH_GUARD_ivBlyIgMoh0KJl1p5J44xFCWiI9nPqRi

#include <cstddef>

namespace breath {

//      count():
//      ========
//
//!     \return
//!         The number of elements of the array argument
//!         (obviously, \c n). See also the file-level documentation.
// -----------------------------------------------------------------------
template< typename T, std::size_t n >
constexpr std::size_t
count( T const ( & )[ n ] ) noexcept
{
    return n ;
}

//      count():
//      ========
//
//!     The same as \c t.size(), for any standard container. See also
//!     the file-level documentation.
// -----------------------------------------------------------------------
template< typename T >
constexpr typename T::size_type
count( T const & t ) noexcept( noexcept( t.size() ) )
{
    return t.size() ;
}

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
