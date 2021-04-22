// ===========================================================================
//                     Copyright 2006-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A cryptographic hash digest.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_HJb5zsPZzS9ztbt5GdVJMPv00mZUAnQI
#define BREEZE_GUARD_HJb5zsPZzS9ztbt5GdVJMPv00mZUAnQI

#include "breeze/top_level_namespace.hpp"
#include "breeze/operator/equality_comparison.hpp"
#include <iosfwd>

namespace breeze_ns {

//      digest:
//      =======
//
//!\brief
//!     The result of applying a digest algorithm to a given input
//!     sequence.
// ---------------------------------------------------------------------------
template< typename Hasher >
class digest
    :   private equality_comparison< digest< Hasher > >
{
public:
    typedef typename Hasher::byte_type const *
                        const_iterator ;

    //!     \name Constructors, destructor and copy assignment
    //!
    //!     `digest` uses the compiler-generated copy constructor,
    //!     destructor and copy assignment operator.
    //!
    //!     The other constructors are listed below.
    //!
    //!\{
    // -----------------------------------------------------------------------
    //!     Constructs a digest from a `Hasher`. Since the `Hasher`
    //!     argument is passed by value its state is not affected.
    // -----------------------------------------------------------------------
    explicit            digest( Hasher hasher_copy ) ;

    //!     Constructs the digest of the range <tt>[begin, end)</tt>.
    //!     This constructor saves the user from constructing a `Hasher`
    //!     object explicitly, but, of course, is only suitable if the
    //!     input range is all available at once. If you need to
    //!     accumulate the input in multiple steps, you'll need to use a
    //!     `Hasher` in your client code, instead.
    // -----------------------------------------------------------------------
    template< typename InputIter >
                        digest( InputIter begin, InputIter end ) ;
    //!\}


    //!     Equality comparison (both `==` and `!=` are provided).
    // -----------------------------------------------------------------------
    bool                is_equal( digest< Hasher > const & ) const ;

    //!     \name Functions for byte-based iteration (read-only)
    //!
    //!     \note
    //!         `const_iterator` is a forward iterator.
    //          [gps]
    //!\{
    const_iterator      begin() const ;
    const_iterator      end() const ;
    //!\}

    class               less ;
    friend class        less ;
    //      less:
    //      =====
    //
    //!     \brief
    //!         A functor to compare digest objects.
    //!
    //!     Implements a strict weak ordering relation between digests
    //!     (from the same `Hasher` type). Useful for ordered
    //!     associative containers.
    //!
    //!     The function call operator is not `noexcept`, and the class
    //!     is a friend, because I'd like this part of the library,
    //!     which is the oldest, to be still compilable as C++03, if
    //!     needed.
    // -----------------------------------------------------------------------
    class               less
    {
    public:
        bool                operator ()( digest< Hasher > const & d1,
                                         digest< Hasher > const & d2 ) const ;
    } ;

private:
    typename Hasher::raw_digest_type
                        m_raw_digest ;
} ;

//!\brief
//!     Outputs a hexadecimal representation of the digest.
//!
//!     The case of the letters A-F is unspecified (this allows us to
//!     support e.g. `std::uppercase` and `std::nouppercase` in the
//!     future). But it's guaranteed that all letters will have the same
//!     case.
// ---------------------------------------------------------------------------
template< typename Hasher >
std::ostream &      operator <<( std::ostream           & os,
                                 digest< Hasher > const & d ) ;

//      make_digest():
//      ==============
//
//!\brief
//!     Convenience function to create a `digest` from a `Hasher` (can
//!     use type deduction).
//!
//!     \return
//!         digest< Hasher >( h )
// ---------------------------------------------------------------------------
template< typename Hasher >
digest< Hasher >    make_digest( Hasher const & h ) ;

}

#include "brz/digest.tpp"
#endif
