// ===========================================================================
//                     Copyright 2006-2021 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A template for "maybe" values.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_93j8pelTutz7YloouImWg9M7REakYYSD
#define BREEZE_GUARD_93j8pelTutz7YloouImWg9M7REakYYSD

#include "breeze/top_level_namespace.hpp"
#include <type_traits>

namespace breeze_ns {

//      boolean_maybe_traits:
//      =====================
//
//!\brief
//!     The default traits class for `maybe`. Logically corresponds to a
//!     boolean (valid/invalid).
// ---------------------------------------------------------------------------
class boolean_maybe_traits
{
public:
    //      status:
    //      =======
    //
    //!\brief
    //!     The type of the status to associate to the `maybe` value.
    // -----------------------------------------------------------------------
    class status
    {
    public:
        explicit            status( bool b ) noexcept : value( b ) {}
        bool                value ;
    } ;

    //!     See the `maybe` documentation.
    // -----------------------------------------------------------------------
    static bool         is_valid( status s ) noexcept
    {
        return s.value ;
    }

    //!     See the `maybe` documentation.
    // -----------------------------------------------------------------------
    static status       default_invalid() noexcept
    {
        return status( false ) ;
    }

    //!     See the `maybe` documentation.
    // -----------------------------------------------------------------------
    static status       default_valid() noexcept
    {
        return status( true ) ;
    }
} ;


//      maybe:
//      ======
//
//!     \copybrief maybe.hpp
//!
//!     A class template to represent "possible" values. The idea was
//!     signaled by James Kanze, and comes from
//!
//!     John J. Barton, Lee R. Nackman (1994). <i>Scientific and
//!     Engineering C++: An Introduction with Advanced Techniques and
//!     Examples</i>. Addison-Wesley Professional. ISBN 0-201-53393-6.
//!
//!     The book calls it "Fallible", but we chose a more general name.
//!     In type theory terminology, `maybe< T >` is an <i>option
//!     type</i>. Many languages support this concept, or the related
//!     concept of <i>nullable type</i>, directly.
//!
//!     Basically: `maybe< T >` is used as return type for functions
//!     that logically return a `T` or fail. The `maybe< T >` object
//!     keeps track of its validity state, and any attempt to retrieve
//!     the `T` object when it is marked as invalid will cause an
//!     assertion failure.
//!
//!     Note that the original Barton and Nackman solution threw an
//!     exception, instead.
//!
//!     The Breeze library guarantees that the `T` object, if any, is
//!     stored as a part of its `maybe` object: no additional storage is
//!     used.
//!
//!     There are other important differences compared to the version
//!     provided by Barton and Nackman.
//!
//!     1. At least for the moment, there is no `invalidate()` function;
//!        I'm still waiting to see if a reasonable usage for it exists
//!        (perhaps a cache?).
//!
//!     2. No conversion function to `T` is provided. Among other
//!        things, it wouldn't be useful in at least the following
//!        situations:
//!
//!         - when you want to invoke a member function on the "real"
//!           object:
//!           ```
//!               maybe< std::string > my_function() ;
//!               my_function().size() ;        // error
//!               my_function().value().size()  // OK
//!           ```
//!
//!           (but, of course, the latter is stylistically rare: one
//!           would usually assign the function return value first)
//!
//!         - when `T` itself has a user defined conversion, which you
//!           want to be applied
//!
//!        As shown above, in these cases you have to explicitly invoke
//!        `value()`.
//!
//!        Curiously enough, Barton and Nackman's book introduces
//!        `Fallible` as an example of using conversions ("to add a
//!        binary state"---valid or invalid---and checking to objects).
//!        The conversion itself, however, isn't part of the concept: it
//!        just makes the checking more "transparent" (at the well-known
//!        cost that implicit conversions generally bring).
//!
//!     3. It isn't required for `T` to have a default constructor.
//!
//!     4. Has a richer interface and supports move semantics.
//!
//!     5. Has an additional template parameter (`Traits`) which allows
//!        specifying several invalid states or several valid states.
//!
//!     The template parameters are:
//!
//!      - `T`
//!
//!        The type of the value to store when the `maybe` is valid. As
//!        usual, its move constructor(s) and move assignment
//!        operator(s), if any, must not emit exceptions.
//!
//!      - `Traits`
//!
//!        A traits class defining the valid and the invalid states of
//!        the `maybe` object. It shall contain:
//!
//!         - a nested type or typedef named "status" that can be used
//!           to store the state of the `maybe` object
//!
//!         - an `%is_valid()` static function, which returns whether a
//!           given value of type `status` corresponds to a valid status
//!           or not
//!
//!         - two static functions, named "default_invalid" and
//!           "default_valid" which give the default invalid and valid
//!           state, respectively
//!
//!        The copy and move operations of `Traits::status` must not
//!        emit exceptions (note that this is a stronger requirement
//!        than the one on `T`, which concerns move only).
//!
//!     \par A final note about std::optional
//!
//!     C++17 introduces `std::optional`, which has the same purpose as
//!     our `maybe`.
//!
//!     Generally, I'm against using components that do double duty with
//!     the standard library, but `std::optional`:
//!
//!      - is IMHO quite over-engineered
//!
//!      - abuses operator overloading to provide a pointer-like syntax
//!        for unchecked access to the contained value
//!
//!      - has an error-prone conversion to `bool` instead of an
//!        `is_valid()` function: see `std::optional< bool >`
//!
//!      - treats a valid `std::optional< T >` as a `T` in some contexts
//!        (comparison operators) and not in others
//!
//!      - doesn't (yet?) support a generalized error status, which is
//!        essential for our usages
//!
//!     So, I'm not going to replace our `maybe` with `std::optional`,
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


    //!\brief
    //!     Constructs an invalid `maybe`.
    //!
    //!     \pre
    //!         ! Traits::is_valid( status )
    //!
    //!     \post
    //!         - ! is_valid()
    //!         - status() == status
    // -----------------------------------------------------------------------
    explicit            maybe( status_type status =
                                          Traits::default_invalid() ) ;

    //!\brief
    //!     Constructs a `maybe` from a `T` lvalue.
    //!
    //!     \pre
    //!         Traits::is_valid( status )
    //!
    //!     \param value
    //!         The `T` value to copy.
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

    //!\brief
    //!     Constructs a `maybe` from a `T` rvalue.
    //!
    //!     \pre
    //!         Traits::is_valid( status )
    //!
    //!     \param value
    //!         The `T` value to move from.
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
                                            Traits::default_valid() ) ;

    //!\brief
    //!     Copy constructs a `maybe`.
    //!
    //!     \post
    //!         - ! is_valid() || value() refers to a copy of
    //!           other.value()
    //!         - status() == other.status()
    // -----------------------------------------------------------------------
                        maybe( maybe const & other ) ;

    //!\brief
    //!     Move constructs a `maybe`.
    //!
    //!     \post
    //!         - value() is moved from other.value()
    //!         - status() == other.status()
    // -----------------------------------------------------------------------
                        maybe( maybe && other ) noexcept ;

    //!\brief
    //!     Destroys the `maybe` and the contained object, if any.
    // -----------------------------------------------------------------------
                        ~maybe() noexcept ;

    //!\brief
    //!     Copy assigns a `maybe`.
    //!
    //!     \post
    //!         - ! is_valid() || value() refers to a copy of
    //!           other.value()
    //!         - status() == other.status()
    // -----------------------------------------------------------------------
    maybe &             operator =( maybe const & other ) ;

    //!\brief
    //!     Move assigns a `maybe`.
    //!
    //!     \post
    //!         - ! is_valid() || value() is moved from other.value()
    //!         - status() == other.status()
    // -----------------------------------------------------------------------
    maybe &             operator =( maybe && other ) noexcept ;

    //!\brief
    //!     Assigns the value from a `T` lvalue.
    //!
    //!     \param value
    //!         The value to copy.
    //!
    //!     \post
    //!         - is_valid()
    //!         - value() refers to a copy of value
    //!         - status == Traits::default_valid()
    // -----------------------------------------------------------------------
    maybe &             operator =( T const & value ) ;

    //!\brief
    //!     Moves the value from a `T` rvalue.
    //!
    //!     \post
    //!         - is_valid()
    //!         - value() is moved from value
    //!         - status() == Traits::default_valid()
    // -----------------------------------------------------------------------
    maybe &             operator =( T && value ) noexcept ;

    //!\brief
    //!     Returns the validity status.
    // -----------------------------------------------------------------------
    status_type         status() const noexcept ;

    //!\brief
    //!     Returns `Traits::is_valid( status() )`.
    // -----------------------------------------------------------------------
    bool                is_valid() const noexcept ;

    //!\brief
    //!     Returns a reference to the contained value.
    //!
    //!     \pre
    //!         is_valid()
    // -----------------------------------------------------------------------
    T const &           value() const ;

    //!\brief
    //!     Returns the contained value or a default.
    //!
    //!     \return
    //!         `value()` if `is_valid()`; otherwise `default_value`.
    //!
    //!     Note that, differently from `value()`, this function returns
    //!     by value, which prevents problems of dangling references.
    //!     Note, too, that, for this reason, it is not noexcept (`T`'s
    //!     copy constructor might throw); a conditional `noexcept()`
    //!     would be an option, but it adds too much complexity, in our
    //!     opinion, and of course we would have to use it consistently,
    //!     not just for `%default_to()`.
    // -----------------------------------------------------------------------
    T                   default_to( T const & default_value ) const ;

private:
    void                construct( T const & value ) ;
    void                construct( T && value ) noexcept ;
    void                destroy() noexcept ;

    T &                 non_const_value() ;

    alignas( T ) unsigned char
                        m_storage[ sizeof( T ) ] ;
    status_type         m_status ;

} ;

}

#include "brz/maybe.tpp"
#endif
