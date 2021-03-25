// ===========================================================================
//                        Copyright 2013 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A set of chars.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_Gq4RCdDZQAIMmQBL7I3lbPfT3oHjV7of
#define BREEZE_GUARD_Gq4RCdDZQAIMmQBL7I3lbPfT3oHjV7of

#include "breeze/top_level_namespace.hpp"
#include <bitset>
#include <climits> // avoid the verbosity of numeric_limits
#include <cstddef>
#include <iterator>
#include <string>

namespace breeze_ns {

//      set_of_chars:
//      =============
//
//!     \copybrief set_of_chars.hpp
//!
//!     With respect to a `std::string`, a `set_of_chars` can't have
//!     duplicates and may model the concept more closely. It also has
//!     different complexity guarantees: adding a `char`, removing a
//!     `char`, and testing if a `char` is in the set are all <tt>O(1)
//!     </tt> operations; on the other hand, incrementing an iterator is
//!     a linear search.
//!
//!     Note that several functions, below, are overloaded on `char` and
//!     `char const *`. Now, depending on whether plain `char` has a
//!     sign, `CHAR_MIN` may expand to a (non-char) null pointer
//!     constant, which means that e.g. the call to `add()` in
//!
//!     ```
//!         set_of_chars sc ;
//!         sc.add( CHAR_MIN ) ;
//!     ```
//!
//!     may be ambiguous. To avoid this ambiguity, write:
//!
//!     ```
//!         sc.add( static_cast< char >( CHAR_MIN ) ) ;
//!     ```
//!
//!     or use
//!
//!     ```
//!         std::numeric_limits< char >::min()
//!     ```
// ---------------------------------------------------------------------------
class set_of_chars
{
public:
    //!     Constructs an empty set.
    //!
    //!     \post
    //!         is_empty()
    // -----------------------------------------------------------------------
                        set_of_chars() noexcept ;

    //!     Constructs a set containing all and only the non-null
    //!     elements of the string pointed to by `s`.
    //!
    //!     \pre
    //!         s != nullptr
    // -----------------------------------------------------------------------
    explicit            set_of_chars( char const * s ) noexcept ;

    //!     Constructs a set containing all and only the characters in
    //!     `s` (including null characters, if any).
    // -----------------------------------------------------------------------
    explicit            set_of_chars( std::string const & s ) noexcept ;

    //!     Constructs a set containing all and only the characters in
    //!     the range `[begin, end)`.
    // -----------------------------------------------------------------------
    template< typename InputIterator>
                        set_of_chars( InputIterator begin, InputIterator end )
                                                                      noexcept ;

    //!     A special type and value used by some constructors.
    // -----------------------------------------------------------------------
    enum except_for { except } ;

    //!     Constructs a set containing all characters except `c`.
    // -----------------------------------------------------------------------
                        set_of_chars( except_for, char c ) noexcept ;

    //!     Constructs a set containing all characters except the
    //!     non-null characters in the string pointed to by `s`.
    //!
    //!     \pre
    //!         s != nullptr
    // -----------------------------------------------------------------------
                        set_of_chars( except_for, char const * s ) noexcept ;

    //!     Constructs a set containing all characters except those in
    //!     `s`.
    // -----------------------------------------------------------------------
                        set_of_chars( except_for, std::string const & s )
                                                                      noexcept ;

    //!     Constructs a copy of `other`.
    //!
    //!     \post
    //!         *this == other
    // -----------------------------------------------------------------------
                        set_of_chars( set_of_chars const & other ) noexcept ;

    //!     Copy-assigns from `other`.
    //!
    //!     \post
    //!         *this == other
    //!
    //!     \note
    //!         All iterators into `*this` are invalidated.
    // -----------------------------------------------------------------------
    set_of_chars &      operator =( set_of_chars const & other ) noexcept ;

    //!     Destroys the set.
    //!
    //!     \note
    //!         All iterators into `*this` are invalidated.
    // -----------------------------------------------------------------------
                        ~set_of_chars() noexcept ;

    //!     Compares `*this` and `other`.
    //!
    //!     \return
    //!         `true` if and only if the two sets contain the same
    //!         characters.
    // -----------------------------------------------------------------------
    bool                operator ==( set_of_chars const & other ) const
                                                                      noexcept ;

    //!     \return
    //!         `true` if an only if `*this` contains the character `c`.
    // -----------------------------------------------------------------------
    bool                contains( char c ) const noexcept ;

    //!     Adds the character `c` to the set.
    //!
    //!     \note
    //!         No iterators are invalidated.
    // -----------------------------------------------------------------------
    set_of_chars &      add( char c ) noexcept ;

    //!     Adds all the non-null characters in the string pointed to by
    //!     `s` to the set.
    //!
    //!     \pre
    //!         s != nullptr
    //!
    //!     \note
    //!         No iterators are invalidated.
    // -----------------------------------------------------------------------
    set_of_chars &      add( char const * s ) ;

    //!     Adds all the characters in `s` to the set.
    //!
    //!     \note
    //!         No iterators are invalidated.
    // -----------------------------------------------------------------------
    set_of_chars &      add( std::string const & s ) noexcept ;

    //!     Adds all the characters in the range `[begin, end)` to the
    //!     set.
    //!
    //!     \note
    //!         No iterators are invalidated.
    // -----------------------------------------------------------------------
    template< typename InputIterator >
    set_of_chars &      add( InputIterator begin, InputIterator end ) noexcept ;

    //!     Removes the character `c` from the set.
    //!
    //!     \note
    //!         All iterators referring to `c` are invalidated.
    // -----------------------------------------------------------------------
    set_of_chars &      remove( char c ) noexcept ;

    //!     Removes all the non-null characters in the string pointed to
    //!     by `s` from the set.
    //!
    //!     \pre
    //!         s != nullptr
    //!
    //!     \note
    //!         All iterators referring to removed characters are
    //!         invalidated.
    // -----------------------------------------------------------------------
    set_of_chars &      remove( char const * s ) ;

    //!     Removes all the characters in `s` from the set.
    //!
    //!     \note
    //!         All iterators referring to removed characters are
    //!         invalidated.
    // -----------------------------------------------------------------------
    set_of_chars &      remove( std::string const & s ) noexcept ;

    //!     Mutates the set into its complement.
    //!
    //!     \note
    //!         All iterators into `*this` are invalidated.
    // -----------------------------------------------------------------------
    void                complement() noexcept ;

    //!     \return
    //!         A string with all and only the characters contained in
    //!         the set.
    // -----------------------------------------------------------------------
    std::string         as_string() const ;

    //!     \return
    //!         The cardinality of the set.
    // -----------------------------------------------------------------------
    std::ptrdiff_t      count() const noexcept ;

    //!     \return
    //!         Whether the set contains no characters.
    // -----------------------------------------------------------------------
    bool                is_empty() const noexcept ;


    class               iterator ;
    friend class        iterator ;
    typedef iterator    const_iterator ;

    //!\{   Read-only iterators for the standard library.
    // -----------------------------------------------------------------------
    iterator            begin() const noexcept ;
    iterator            end() const noexcept ;

    const_iterator      cbegin() const noexcept ;
    const_iterator      cend() const noexcept ;
    //!\}

private:
    enum { size = CHAR_MAX - CHAR_MIN + 1 } ;
    typedef std::bitset< size >
                        bits_type ;
    typedef int         index_type ;
    bits_type           m_bits ;

    static index_type   to_index( char c ) noexcept ;
    static char         to_char( index_type index ) noexcept ;

public:
    //      iterator:
    //      =========
    //
    //!     \brief
    //!         An iterator for the set.
    //!
    //!     Iterates over all of the characters in the set. It is a \e
    //!     constant forward iterator (`iterator` and `const_iterator`
    //!     have the same semantics).
    // -----------------------------------------------------------------------
    class               iterator
    {
    public:
        //!\name Typedefs for the standard library
        //!\{
        // -------------------------------------------------------------------
        typedef std::forward_iterator_tag
                            iterator_category  ;
        typedef char        value_type         ;
        typedef int         difference_type    ;
        typedef char const *pointer            ;
        typedef char const &reference          ;
        //!\}

        //!     Constructs a one-past-the-end iterator.
        // -------------------------------------------------------------------
                            iterator() noexcept ;

        //!     Constructs an iterator to the first character in `sc`.
        // -------------------------------------------------------------------
        explicit            iterator( set_of_chars const & sc ) noexcept ;

        //!\name Iterator operations
        //!\{
        // -------------------------------------------------------------------
        value_type          operator *() const noexcept ;
        iterator &          operator ++() & noexcept ;
        iterator            operator ++( int ) & noexcept ;

        //!     \note
        //!         It's undefined behavior to compare iterators into
        //!         different objects.
        // -------------------------------------------------------------------
        bool                operator ==( iterator const & ) const noexcept ;

        //!     \note
        //!         It's undefined behavior to compare iterators into
        //!         different objects.
        // -------------------------------------------------------------------
        bool                operator !=( iterator const & ) const noexcept ;
        //!\}

    private:
        bits_type const *   m_owner ;
        index_type          m_index ;

        void                increment() noexcept ;
        void                assert_refers_to_a_char() const ;
    } ;
} ;

template< typename InputIterator>
set_of_chars::set_of_chars( InputIterator begin, InputIterator end ) noexcept
    :   m_bits()
{
    add( begin, end ) ;
}

template< typename InputIterator >
set_of_chars &
set_of_chars::add( InputIterator begin, InputIterator end ) noexcept
{
    while ( begin != end ) {
        add( *begin ) ;
        ++ begin ;
    }
    return *this ;
}

}

#endif
