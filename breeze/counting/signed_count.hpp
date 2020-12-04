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
//!     The syntax is, uniformly, \c breeze::signed_count( a )
//!     regardless of the actual type of \c a. See also begin_end.hpp.
//!
//!     Following C++ best practices, these templates return a \e signed
//!     integer. They are made obsolete in C++20 by the namespace-scope
//!     \c std::ssize()'s. However our version avoids any fancy
//!     derivation of the return type, even for containers.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_ivBlyIgMoh0KJl1p5J44xFCWiI9nPqRi
#define BREEZE_GUARD_ivBlyIgMoh0KJl1p5J44xFCWiI9nPqRi

#include "breeze/top_level_namespace.hpp"
#include "breeze/diagnostics/assert.hpp"
#include "breeze/preprocessing/prevent_macro_expansion.hpp"
#include <cstddef>
#include <limits>

namespace breeze_ns {

//      signed_count():
//      ===============
//
//!     \return
//!         The number of elements of the array argument (obviously, \c
//!         n). See also the file-level documentation.
// ---------------------------------------------------------------------------
template< typename T, std::ptrdiff_t n >
constexpr std::ptrdiff_t
signed_count( T const ( & )[ n ] ) noexcept
{
    return n ;
}

//      signed_count():
//      ===============
//
//!     \return
//!         The value of \c t.size() converted to \c std::ptrdiff_t. See
//!         also the file-level documentation.
// ---------------------------------------------------------------------------
template< typename T >
constexpr std::ptrdiff_t
signed_count( T const & t )
{
    typedef std::ptrdiff_t
                        return_type ;

    std::size_t const   max = std::numeric_limits< return_type >::max
                                BREEZE_PREVENT_MACRO_EXPANSION () ;

    BREEZE_ASSERT( t.size() <= max ) ;
    return static_cast< return_type >( t.size() ) ;
}

}

#endif
