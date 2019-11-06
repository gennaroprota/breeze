// ===========================================================================
//                     Copyright 2006-2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Namespace-scope \c begin() and \c end().
//!
//!     Syntax adaptors to extend the usage of begin() and end() to
//!     C-style arrays. Also defines cbegin() and cend(), with the
//!     same extent.
//!
//!     All of the function templates are non-members, and the
//!     syntax is, uniformly
//!
//!     <code>
//!         breath::begin( a ) ;
//!         breath::end( a ) ;
//!     </code>
//!
//!     regardless of whether \c a refers to a standard container or
//!     to a built-in array. See also count.hpp.
//!
//!     NOTE: C++11 introduced templates like these and C++17 makes
//!     them almost equivalent to ours. New code should use the
//!     standard versions and ours should just go with time. The only
//!     reason these are still around is that I haven't had time
//!     to update the code that uses them.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_Ve2uzZNiUDgCTZXgV1iB3bUD5U0n1kKD
#define BREATH_GUARD_Ve2uzZNiUDgCTZXgV1iB3bUD5U0n1kKD

#include <cstddef>

namespace breath {

//      begin():
//      ========
//
//!     \return
//!         The same as c.begin(), for any standard container.
// ---------------------------------------------------------------------------
template< typename C >
constexpr typename C::iterator
begin( C & c ) noexcept( noexcept( c.begin() ) )
{
    return c.begin() ;
}

//      begin():
//      ========
//
//!     \return
//!         The same as c.begin(), for any standard container.
// ---------------------------------------------------------------------------
template< typename C >
constexpr typename C::const_iterator
begin( C const & c ) noexcept( noexcept( c.begin() ) )
{
    return c.begin() ;
}

//      cbegin():
//      =========
//
//!     \return
//!         The same as c.begin(), for any standard container.
// ---------------------------------------------------------------------------
template< typename C >
constexpr typename C::const_iterator
cbegin( C const & c ) noexcept( noexcept( c.begin() ) )
{
    return c.begin() ;
}

//      end():
//      ======
//
//!     \return
//!         The same as c.end(), for any standard container.
// ---------------------------------------------------------------------------
template< typename C >
constexpr typename C::iterator
end( C & c ) noexcept( noexcept( c.end() ) )
{
    return c.end() ;
}

//      end():
//      ======
//
//!     \return
//!         The same as c.end(), for any standard container.
// ---------------------------------------------------------------------------
template< typename C >
constexpr typename C::const_iterator
end( C const & c ) noexcept( noexcept( c.end() ) )
{
    return c.end() ;
}

//      cend():
//      =======
//
//!     \return
//!         The same as c.end(), for any standard container.
// ---------------------------------------------------------------------------
template< typename C >
constexpr typename C::const_iterator
cend( C const & c ) noexcept( noexcept( c.end() ) )
{
    return c.end() ;
}

//      begin():
//      ========
//
//!     Like container::begin, but for a built-in array.
//!
//!     (Note that there's no need for a "T const overload".)
// ---------------------------------------------------------------------------
template< typename T, std::size_t n >
constexpr T *
begin( T ( &a )[ n ] ) noexcept
{
    return a ;
}

//      cbegin():
//      =========
//
//!     Like container::begin, but for a built-in array.
// ---------------------------------------------------------------------------
template< typename T, std::size_t n >
constexpr T const *
cbegin( T const ( &a )[ n ] ) noexcept
{
    return a ;
}

//      end():
//      ======
//
//!     Like container::end, but for a built-in array.
//
//!     (The remark about begin() and overloading on const applies
//!     here as well.)
// ---------------------------------------------------------------------------
template< typename T, std::size_t n >
constexpr T *
end( T ( &a )[ n ] ) noexcept
{
    return a + n ;
}

//      cend():
//      =======
//
//!     Like container::end, but for a built-in array.
// ---------------------------------------------------------------------------
template< typename T, std::size_t n >
constexpr T const *
cend( T const ( &a )[ n ] ) noexcept
{
    return a + n ;
}

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
