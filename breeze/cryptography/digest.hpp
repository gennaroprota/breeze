// ===========================================================================
//                     Copyright 2006-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Cryptographic hash digest object.
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
//!     \brief
//!         The result of applying a digest algorithm to a given input
//!         sequence.
// ---------------------------------------------------------------------------
template< typename Hasher >
class digest
    :   private equality_comparison< digest< Hasher > >
{
public:
    typedef typename Hasher::byte_type const *
                        const_iterator ;

    //!\name Initialization
    //!\{
    //!     Constructs a digest from a \c Hasher. Since the \c Hasher
    //!     argument is passed by value its state is not affected.
    // -----------------------------------------------------------------------
    explicit            digest( Hasher hasher_copy ) ;

    //!     Constructs the digest of the range <tt>[begin, end)</tt>.
    //!     This constructor saves the user from constructing a \c
    //!     Hasher object explicitly, but, of course, is only suitable
    //!     if the input range is all available at once. If you need to
    //!     accumulate the input in multiple steps, you'll need to use a
    //!     \c Hasher in your client code, instead.
    // -----------------------------------------------------------------------
    template< typename InputIter >
                        digest( InputIter begin, InputIter end ) ;
    //!\}

    //!     Copy and destruction.
    //!     Compiler-generated copy constructor, copy assignment
    //!     operator and destructor.
    // -----------------------------------------------------------------------


    //!     Equality comparison (both \c == and \c != are provided).
    // -----------------------------------------------------------------------
    bool                is_equal( digest< Hasher > const & ) const ;

    //!\name Byte-based iteration (read-only)
    //!           const_iterator is a forward iterator - gps
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
    //!     (from the same \c Hasher type). Useful for ordered
    //!     associative containers.
    //!
    //!     The function call operator is not \c noexcept, and the class
    //!     is a \c friend, because I'd like this part of the library,
    //!     which is the oldest, to be still compilable as C++03, if
    //!     needed.
    // -----------------------------------------------------------------------
    class               less
    {
    public:
        bool                operator()( digest< Hasher > const & d1,
                                        digest< Hasher > const & d2 ) const ;
    } ;

private:
    typename Hasher::raw_digest_type
                        m_raw_digest ;
} ;

//!     Outputs a hexadecimal representation of the digest. The case of
//!     the letters A-F is unspecified (this allows us to support e.g.
//!     \c std::uppercase and \c std::nouppercase in the future). But
//!     it's guaranteed that all letters will have the same case.
// ---------------------------------------------------------------------------
template< typename Hasher >
std::ostream &      operator <<( std::ostream           & os,
                                 digest< Hasher > const & d ) ;

//      make_digest():
//      ==============
//
//!     Convenience function to create a \c digest from a \c Hasher (can
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

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
