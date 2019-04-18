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

#ifndef BREATH_GUARD_Gq4RCdDZQAIMmQBL7I3lbPfT3oHjV7of
#define BREATH_GUARD_Gq4RCdDZQAIMmQBL7I3lbPfT3oHjV7of

#include <bitset>
#include <climits>
#include <cstddef>
#include <iterator>
#include <string>

namespace breath {

//      set_of_chars:
//      =============
//
//!     A set of chars.
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
    //!     elements of the string pointed to by \c s.
    // -----------------------------------------------------------------------
    explicit            set_of_chars( char const * s ) noexcept ;

    //!     Constructs a set containing all and only the characters in
    //!     \c s (including null characters, if any).
    // -----------------------------------------------------------------------
    explicit            set_of_chars( std::string const & s ) noexcept ;

    //!     Constructs a set containing all and only the characters in
    //!     the range <code>[begin, end)</code>.
    // -----------------------------------------------------------------------
    template< typename FwdIterator>
                        set_of_chars( FwdIterator begin, FwdIterator end )
                                                                      noexcept ;

    //!     A special value used by some constructors.
    // -----------------------------------------------------------------------
    enum except_for { except } ;

    //!     Constructs a set containing all characters except \c c.
    // -----------------------------------------------------------------------
                        set_of_chars( except_for, char c ) noexcept ;

    //!     Constructs a set containing all characters except the
    //!     non-null characters in the string pointed to by \c s.
    // -----------------------------------------------------------------------
                        set_of_chars( except_for, char const * s ) noexcept ;

    //!     Constructs a set containing all characters except those in
    //!     \c s.
    // -----------------------------------------------------------------------
                        set_of_chars( except_for, std::string const & s )
                                                                      noexcept ;

    //!     Constructs a copy of \c other.
    //!
    //!     \post
    //!         *this == other
    // -----------------------------------------------------------------------
                        set_of_chars( set_of_chars const & other ) noexcept ;

    //!     Copy-assigns from \c other.
    //!
    //!     \post
    //!         *this == other
    // -----------------------------------------------------------------------
    set_of_chars &      operator =( set_of_chars const & other ) noexcept ;

    //!     Destroys the set.
    // -----------------------------------------------------------------------
                        ~set_of_chars() noexcept ;

    //!     Compares \c *this and \c other.
    //!
    //!     \return
    //!         \c true if and only if the two sets contain the same
    //!         characters.
    // -----------------------------------------------------------------------
    bool                operator ==( set_of_chars const & other ) const
                                                                      noexcept ;

    //!     \return
    //!         \c true if an only if \c *this contains the character
    //!         \c c.
    // -----------------------------------------------------------------------
    bool                contains( char c ) const noexcept ;

    //!     Adds the character \c c to the set.
    // -----------------------------------------------------------------------
    set_of_chars &      add( char c ) noexcept ;

    //!     Adds all the non-null characters in the string pointed to by
    //!     \c s to the set.
    // -----------------------------------------------------------------------
    set_of_chars &      add( char const * s ) noexcept ;

    //!     Adds all the characters in \c s to the set.
    // -----------------------------------------------------------------------
    set_of_chars &      add( std::string const & s ) noexcept ;

    //!     Adds all the characters in the range <code>[begin, end)
    //!     </code> to the set.
    // -----------------------------------------------------------------------
    template< typename FwdIterator >
    set_of_chars &      add( FwdIterator begin, FwdIterator end ) noexcept ;

    //!     Removes the character \c c from the set.
    // -----------------------------------------------------------------------
    set_of_chars &      remove( char c ) noexcept ;

    //!     Removes all the non-null characters in the string pointed to
    //!     by \c s from the set.
    // -----------------------------------------------------------------------
    set_of_chars &      remove( char const * s ) noexcept ;

    //!     Removes all the characters in \c s from the set.
    // -----------------------------------------------------------------------
    set_of_chars &      remove( std::string const & s ) noexcept ;

    //!     Mutates the set into its complement.
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
    std::size_t         count() const noexcept ;

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
    typedef std::size_t index_type ;
    bits_type           m_bits ;

    static int          to_index( char c ) noexcept ;

public:
    //      iterator:
    //      =========
    //
    //!     An iterator for the set.
    //!
    //!     Iterates over all of the characters in the set.  It is a
    //!     forward iterator.
    // -----------------------------------------------------------------------
    class               iterator
    {
    public:
        //!\{   Typedefs for the standard library.
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

        //!     Constructs an iterator to the first character in \c sc.
        // -------------------------------------------------------------------
        explicit            iterator( set_of_chars const & sc ) noexcept ;

        //!\{   Iterator operations.
        // -------------------------------------------------------------------
        value_type          operator * () const noexcept ;
        iterator &          operator ++() noexcept ;
        iterator            operator ++( int ) noexcept ;

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
    } ;
} ;

template< typename FwdIterator>
set_of_chars::set_of_chars( FwdIterator begin, FwdIterator end ) noexcept
    :   m_bits()
{
    add( begin, end ) ;
}

template< typename FwdIterator >
set_of_chars &
set_of_chars::add( FwdIterator begin, FwdIterator end ) noexcept
{
    while ( begin != end ) {
        add( *begin ) ;
        ++ begin ;
    }
    return *this ;
}

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
