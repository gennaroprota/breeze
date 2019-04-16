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
                        set_of_chars() ;
    explicit            set_of_chars( char const * ) ;
    explicit            set_of_chars( std::string const & ) ;
    template< typename FwdIterator>
                        set_of_chars( FwdIterator begin, FwdIterator end ) ;

    //!     A special value used by some constructors.
    // -----------------------------------------------------------------------
    enum except_for { except } ;

                        set_of_chars( except_for, char ) ;
                        set_of_chars( except_for, char const * ) ;
                        set_of_chars( except_for, std::string const & ) ;

                        set_of_chars( set_of_chars const & ) ;
    set_of_chars &      operator =( set_of_chars const & ) ;

                        ~set_of_chars() noexcept ;

    bool                operator ==( set_of_chars const & ) const ;
    bool                contains( char c ) const ;

    set_of_chars &      add( char c ) ;
    set_of_chars &      add( char const * ) ;
    set_of_chars &      add( std::string const & ) ;
    template< typename FwdIterator >
    set_of_chars &      add( FwdIterator begin, FwdIterator end ) ;

    set_of_chars &      remove( char c ) ;
    set_of_chars &      remove( char const * ) ;
    set_of_chars &      remove( std::string const & ) ;

    void                complement() ;

    std::string         as_string() const ;

    std::size_t         count() const ;
    bool                is_empty() const ;


    class               iterator ;
    friend class        iterator ;
    typedef iterator    const_iterator ;

    //!     Read-only iterators for the standard library.
    // -----------------------------------------------------------------------
    iterator            begin() const ;
    iterator            end() const ;

    const_iterator      cbegin() const ;
    const_iterator      cend() const ;

private:
    enum { size = CHAR_MAX - CHAR_MIN + 1 } ;
    typedef std::bitset< size >
                        bits_type ;
    typedef std::size_t index_type ;
    bits_type           m_bits ;

public:
    //      iterator:
    //      =========
    //
    //!     An iterator for the set.
    //
    //!     Iterates over all of the characters in the set.  It is a
    //!     forward iterator.
    // -----------------------------------------------------------------------
    class               iterator
    {
    public:
        //!     Typedefs for the Standard Library
        // -------------------------------------------------------------------
        typedef std::forward_iterator_tag
                            iterator_category  ;
        typedef char        value_type         ;
        typedef int         difference_type    ;
        typedef char const *pointer            ;
        typedef char const &reference          ;

                            iterator() ;
        explicit            iterator( set_of_chars const & sc ) ;
        value_type          operator * () const ;
        iterator &          operator ++() ;
        iterator            operator ++( int ) ;
        bool                operator ==( iterator const & ) const ;
        bool                operator !=( iterator const & ) const ;

    private:
        enum { infinity = size } ;
        bits_type const *   m_owner ;
        index_type          m_index ;
    } ;
} ;

template< typename FwdIterator>
set_of_chars::set_of_chars( FwdIterator begin, FwdIterator end )
    :   m_bits()
{
    add( begin, end ) ;
}

template< typename FwdIterator >
set_of_chars &
set_of_chars::add( FwdIterator begin, FwdIterator end )
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
