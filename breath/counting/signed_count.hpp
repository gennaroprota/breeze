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
//!     The syntax is, uniformly, \c breath::signed_count( a )
//!     regardless of the actual type of \c a. See also begin_end.hpp.
//!
//!     Following C++ best practices, these templates return a \e signed
//!     integer. They are made obsolete in C++20 by the namespace-scope
//!     \c std::ssize()'s. However our version avoids any fancy
//!     derivation of the return type, even for containers.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_ivBlyIgMoh0KJl1p5J44xFCWiI9nPqRi
#define BREATH_GUARD_ivBlyIgMoh0KJl1p5J44xFCWiI9nPqRi

#include "breath/top_level_namespace.hpp"
#include "breath/diagnostics/assert.hpp"
#include "breath/preprocessing/prevent_macro_expansion.hpp"
#include <cstddef>
#include <limits>

namespace breath_ns {

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

    BREATH_ASSERT(
        t.size() <= std::numeric_limits< return_type >::max
                                        BREATH_PREVENT_MACRO_EXPANSION ()
        ) ;
    return static_cast< return_type >( t.size() ) ;
}

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
