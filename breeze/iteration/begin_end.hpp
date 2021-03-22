// ===========================================================================
//                     Copyright 2006-2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Namespace-scope \c begin()/end() and \c cbegin()/cend().
//!
//!     Syntax adaptors to extend the usage of begin() and end() to
//!     C-style arrays. Also defines cbegin() and cend(), with the same
//!     extent.
//!
//!     All of the function templates are non-members, and the syntax
//!     is, uniformly
//!
//!     \code
//!         breeze::begin( a ) ;
//!         breeze::end( a ) ;
//!     \endcode
//!
//!     regardless of whether \c a refers to a standard container or to
//!     a built-in array.
//!
//!     \note
//!         C++11 and C++14 introduced templates like these and C++17
//!         made them almost equivalent to ours. Ideally, new code
//!         should use the standard versions, and ours should just go.
//!         But the standard <code>cbegin()</code>/<code>cend()</code>
//!         reserve, as common in C++, a surprise: they don't
//!         necessarily return an iterator to const (!). So, I'll keep
//!         my versions around.
//!
//!     \see
//!         signed_count().
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_Ve2uzZNiUDgCTZXgV1iB3bUD5U0n1kKD
#define BREEZE_GUARD_Ve2uzZNiUDgCTZXgV1iB3bUD5U0n1kKD

#include "breeze/top_level_namespace.hpp"
#include <cstddef>

namespace breeze_ns {

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
//!     Like container::end(), but for a built-in array.
//!
//!     (The remark, made for \c begin(), that there's no need for a "T
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
