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
//!     Following C++ best practices, these templates return a \e signed
//!     integer.
//!
//!     These functions are made obsolete in C++20 by the namespace
//!     scope std::ssize()'s. However our version uses, for containers,
//!     a conditional noexcept that the standard version is not
//!     required to have.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_ivBlyIgMoh0KJl1p5J44xFCWiI9nPqRi
#define BREATH_GUARD_ivBlyIgMoh0KJl1p5J44xFCWiI9nPqRi

#include <cstddef>
#include <type_traits>

namespace breath {

//      signed_count():
//      ===============
//
//!     \return
//!         The number of elements of the array argument
//!         (obviously, \c n). See also the file-level documentation.
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
//!         The value of \c t.size() converted to the corresponding
//!         signed type. See also the file-level documentation.
// ---------------------------------------------------------------------------
template< typename T >
constexpr auto
signed_count( T const & t ) noexcept( noexcept( t.size() ) ) ->
                                    std::make_signed_t< decltype( t.size() ) >
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
