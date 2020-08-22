// ===========================================================================
//                     Copyright 2006-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A template for "maybe" values.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_93j8pelTutz7YloouImWg9M7REakYYSD
#define BREATH_GUARD_93j8pelTutz7YloouImWg9M7REakYYSD

#include "breath/top_level_namespace.hpp"
#include "breath/alignment/aligned_storage_for.hpp"
#include <type_traits>

namespace breath_ns {

//      boolean_maybe_traits:
//      =====================
//
//!     The default traits class for \c maybe. Logically corresponds to
//!     a boolean (valid/invalid).
// ---------------------------------------------------------------------------
class boolean_maybe_traits
{
public:
    //      status:
    //      =======
    //
    //!     The type of the status to associate to the \c maybe value.
    // -----------------------------------------------------------------------
    class status
    {
    public:
        explicit            status( bool b ) noexcept : m_status( b ) {}
        bool                m_status ;
    } ;

    //!     See the \c maybe documentation.
    // -----------------------------------------------------------------------
    static bool         is_valid( status s ) noexcept
    {
        return s.m_status ;
    }

    //!     See the \c maybe documentation.
    // -----------------------------------------------------------------------
    static status       default_invalid() noexcept
    {
        return status( false ) ;
    }

    //!     See the \c maybe documentation.
    // -----------------------------------------------------------------------
    static status       default_valid() noexcept
    {
        return status( true ) ;
    }
} ;


//      maybe:
//      ======
//
//!     A class template to represent "possible" values. The idea was
//!     signaled by James Kanze, and comes from
//!
//!         John J. Barton, Lee R. Nackman (1994).
//!         Scientific and Engineering C++: An Introduction with
//!         Advanced Techniques and Examples. Addison-Wesley
//!         Professional. ISBN 0-201-53393-6.
//!
//!     which calls it "Fallible".
//!     Basically: \c maybe< T > is used as return type for functions
//!     that logically return a \c T or fail (thus, it is an intrusive,
//!     although lightweight, solution). The \c maybe< T > object
//!     keeps track of its validity state, and any attempt to retrieve
//!     the \c T object when it is marked as invalid will cause an
//!     assertion failure.
//!
//!     Note that the original Barton and Nackman solution threw an
//!     exception, instead.
//!
//!     The library guarantees that the \c T object, if any, is stored
//!     as a part of its \c maybe object: no additional storage is used.
//!
//!     There are other important differences compared to the version
//!     provided by Barton and Nackman.
//!
//!     1. At least for the moment, there is no \c invalidate()
//!        function; I'm still waiting to see if a reasonable usage for
//!        it exists (perhaps a cache?).
//!
//!     2. No conversion function to \c T is provided. Among other
//!        things, it wouldn't be useful in at least the following
//!        situations:
//!
//!         - when you want to invoke a member function on the "real"
//!           object:
//!
//!           \code
//!               maybe< std::string > my_function() ;
//!               my_function().size() ;        // error
//!               my_function().value().size()  // OK
//!           \endcode
//!
//!           (but, of course, the latter is stylistically rare: one
//!           would usually assign the function return value first)
//!
//!         - when \c T itself has a user defined conversion, which
//!           you want to be applied
//!
//!        As shown above, in these cases you have to explicitly
//!        invoke \c value().
//!
//!        Curiously enough, B&N's book introduces \c Fallible as an
//!        example of using conversions "to add a binary state"---valid
//!        or invalid---and checking to objects. The conversion itself,
//!        however, isn't part of the concept: it just makes the
//!        checking more "transparent" (at the well-known cost that
//!        implicit conversions generally bring).
//!
//!     3. It isn't required for \c T to have a default constructor.
//!
//!     4. Has a richer interface and supports move semantics.
//!
//!     5. Has an additional template parameter (\c Traits) which allows
//!        specifying several invalid states or several valid states.
//!
//!     The template parameters are:
//!
//!      - \c T
//!
//!        The type of the value to store when the \c maybe is valid. As
//!        usual, its move constructor(s) and move assignment
//!        operator(s), if any, must not emit exceptions.
//!
//!      - \c Traits
//!
//!        A traits class defining the valid and the invalid states of
//!        the \c maybe object. It shall contain:
//!
//!         - a nested type or typedef named "status" that can be used
//!           to store the state of the \c maybe object
//!
//!         - an \c %is_valid() static function, which returns whether a
//!           given value of type \c status corresponds to a valid
//!           status or not
//!
//!         - two static functions, named "default_invalid" and
//!           "default_valid" which give the default invalid and valid
//!           state, respectively
//!
//!        The copy and move operations of \c Traits::status must not
//!        emit exceptions (note that this is a stronger requirement
//!        than the one on \c T, which concerns move only).
//!
//!     A final note about std::optional
//!     --------------------------------
//!
//!     C++17 introduces \c std::optional, which has the same purpose as
//!     \c maybe.
//!
//!     Generally, I'm against using components that do double duty with
//!     the standard library, but \c std::optional:
//!
//!      - is IMHO quite over-engineered
//!
//!      - abuses operator overloading to provide a pointer-like syntax
//!        for unchecked access to the contained value
//!
//!      - has an error-prone conversion to \c bool for \c is_valid():
//!        see \c std::optional< bool >
//!
//!      - treats a valid \c std::optional< T > as a \c T in some
//!        contexts (comparison operators) and not in others
//!
//!      - doesn't (yet?) support a generalized error status, which is
//!        essential for our usages
//!
//!     So, I'm not going to replace our \c maybe with \c std::optional,
//!     even in C++17.
// ---------------------------------------------------------------------------
template< typename T, typename Traits = boolean_maybe_traits >
class maybe
{
public:
    typedef T           value_type ;
    typedef typename Traits::status
                        status_type ;

    //      These static_asserts are ugly but... better having them.
    //      They might be a bit less unpleasant in C++17, if we remove
    //      the empty message. [FUTURE]
    //
    //      Note: the static_assert on the move assignment of value_type
    //      has been excluded to cope with the case value_type ==
    //      std::string. Because, in that case, the static_assert might
    //      pass or not depending on the implementation (there was, in
    //      fact, a DR on the noexcept specification of basic_string's
    //      move assignment operator---LWG 2063---but it was only
    //      resolved for C++17; formally, in C++11 and C++14, the
    //      operator should have an unconditional noexcept, despite that
    //      being known as incorrect in virtue of that DR, but
    //      implementations vary).
    //
    //      We leave the static_assert commented out, as a reminder to
    //      enable it when we'll require at least C++17. [FUTURE]
    // -----------------------------------------------------------------------
    static_assert( std::is_nothrow_move_constructible< value_type >::value,
                                                                          "" ) ;
    // static_assert( std::is_nothrow_move_assignable< value_type >::value,
    //                                                                    "" ) ;

    static_assert( std::is_nothrow_copy_constructible< status_type >::value,
                                                                          "" ) ;
    static_assert( std::is_nothrow_copy_assignable< status_type >::value, "" ) ;
    static_assert( std::is_nothrow_move_constructible< status_type >::value,
                                                                          "" ) ;
    static_assert( std::is_nothrow_move_assignable< status_type >::value, "" ) ;


    //!     Constructs an invalid \c maybe.
    //!
    //!     \pre
    //!         ! Traits::is_valid( status )
    //!
    //!     \post
    //!         - ! is_valid()
    //!         - status() == status
    // -----------------------------------------------------------------------
    explicit            maybe( status_type status =
                                          Traits::default_invalid() ) noexcept ;

    //!     Constructs a valid \c maybe.
    //!
    //!     \pre
    //!         Traits::is_valid( status )
    //!
    //!     \param value
    //!         The \c T value to copy.
    //!
    //!     \param status
    //!         The status to associate to the object.
    //!
    //!     \post
    //!         - is_valid()
    //!         - value() refers to a copy of value
    //!         - status() == status
    // -----------------------------------------------------------------------
    explicit            maybe( T const & value, status_type status =
                                                     Traits::default_valid() ) ;

    //!     \pre
    //!         Traits::is_valid( status )
    //!
    //!     \param value
    //!         The \c T value to move from.
    //!
    //!     \param status
    //!         The status to associate to the object
    //!
    //!     \post
    //!         - is_valid()
    //!         - value() is moved from value
    //!         - status() == status
    // -----------------------------------------------------------------------
    explicit            maybe( T && value, status_type status =
                                            Traits::default_valid() ) noexcept ;

    //!     \post
    //!         - ! is_valid() || value() refers to a copy of
    //!           other.value()
    //!         - status() == other.status()
    // -----------------------------------------------------------------------
                        maybe( maybe const & other ) ;

    //!     \post
    //!         - value() is moved from other.value()
    //!         - status() == other.status()
    // -----------------------------------------------------------------------
                        maybe( maybe && other ) noexcept ;

                        ~maybe() noexcept ;

    //!     \post
    //!         - ! is_valid() || value() refers to a copy of
    //!           other.value()
    //!         - status() == other.status()
    // -----------------------------------------------------------------------
    maybe &             operator =( maybe const & other ) ;

    //!     \post
    //!         - ! is_valid() || value() is moved from other.value()
    //!         - status() == other.status()
    // -----------------------------------------------------------------------
    maybe &             operator =( maybe && other ) noexcept ;

    //!     \param value
    //!         The value to copy.
    //!
    //!     \post
    //!         - is_valid()
    //!         - value() refers to a copy of value
    //!         - status == Traits::default_valid()
    // -----------------------------------------------------------------------
    maybe &             operator =( T const & value ) ;

    //!     \post
    //!         - is_valid()
    //!         - value() is moved from value
    //!         - status() == Traits::default_valid()
    // -----------------------------------------------------------------------
    maybe &             operator =( T && value ) noexcept ;

    //!     \return
    //!         The validity status.
    // -----------------------------------------------------------------------
    status_type         status() const noexcept ;

    //!     \return
    //!         Traits::is_valid( status() )
    // -----------------------------------------------------------------------
    bool                is_valid() const noexcept ;

    //!     \return
    //!         A reference to the \c T value.
    //!
    //!     \pre
    //!         is_valid()
    // -----------------------------------------------------------------------
    T const &           value() const noexcept ;

    //!     \return
    //!         \c value() if \c is_valid(); otherwise \c default_value.
    //!
    //!     Note that, differently from \c value(), this function
    //!     returns by value, which prevents problems of dangling
    //!     references. Note, too, that, for this reason, it is not
    //!     noexcept (\c T's copy constructor might throw); a
    //!     conditional noexcept() would be an option, but it adds too
    //!     much complexity, in our opinion, and of course we would have
    //!     to use it consistently, not just for \c %default_to().
    // -----------------------------------------------------------------------
    T                   default_to( T const & default_value ) const ;

private:
    void                construct( T const & value ) ;
    void                construct( T && value ) noexcept ;
    void                destroy() noexcept ;

    T &                 non_const_value() noexcept ;

    aligned_storage_for< T >
                        m_storage ;
    status_type         m_status ;

} ;

}

#include "brt/maybe.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
