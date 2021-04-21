// ===========================================================================
//                     Copyright 2006-2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Namespace-scope `begin()`/`end()` and
//!            `cbegin()`/`cend()`.
//!
//!     Syntax adaptors to extend the usage of begin() and end() to
//!     C-style arrays. Also defines cbegin() and cend(), with the same
//!     extent.
//!
//!     All of the function templates are non-members, and the syntax
//!     is, uniformly
//!
//!     ```
//!         breeze::begin( a ) ;
//!         breeze::end( a ) ;
//!     ```
//!
//!     regardless of whether `a` refers to a standard container or to a
//!     built-in array.
//!
//!     \note
//!         C++11 and C++14 introduced templates like these and C++17
//!         made them almost equivalent to ours. Ideally, new code
//!         should use the standard versions, and ours should just go.
//!         But the standard `cbegin()`/`cend()` reserve, as common in
//!         C++, a surprise: they don't necessarily return an iterator
//!         to const (!). So, I'll keep my versions around.
//!
//!     \see
//!         signed_count().
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_Ve2uzZNiUDgCTZXgV1iB3bUD5U0n1kKD
#define BREEZE_GUARD_Ve2uzZNiUDgCTZXgV1iB3bUD5U0n1kKD

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//      begin():
//      ========
//
//!\brief
//!     Returns the same as c.begin(), for any standard container.
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
//!\brief
//!     Returns the same as c.begin(), for any standard container.
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
//!\brief
//!     Returns the same as c.begin(), for any standard container.
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
//!\brief
//!     Returns the same as c.end(), for any standard container.
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
//!\brief
//!     Returns the same as c.end(), for any standard container.
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
//!\brief
//!     Returns the same as c.end(), for any standard container.
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
//!\brief
//!     Like container::begin(), but for a built-in array.
//!
//!     (Note that there's no need for a "T const overload".)
// ---------------------------------------------------------------------------
template< typename T, long long n >
constexpr T *
begin( T ( &a )[ n ] ) noexcept
{
    return a ;
}

//      cbegin():
//      =========
//
//!\brief
//!     Like container::begin(), but for a built-in array.
// ---------------------------------------------------------------------------
template< typename T, long long n >
constexpr T const *
cbegin( T const ( &a )[ n ] ) noexcept
{
    return a ;
}

//      end():
//      ======
//
//!\brief
//!     Like container::end(), but for a built-in array.
//!
//!     (The remark, made for `begin()`, that there's no need for a "T
//!     const overload" applies here, as well.)
// ---------------------------------------------------------------------------
template< typename T, long long n >
constexpr T *
end( T ( &a )[ n ] ) noexcept
{
    return a + n ;
}

//      cend():
//      =======
//
//!\brief
//!     Like container::end(), but for a built-in array.
// ---------------------------------------------------------------------------
template< typename T, long long n >
constexpr T const *
cend( T const ( &a )[ n ] ) noexcept
{
    return a + n ;
}

}

#endif
