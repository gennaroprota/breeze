// ===========================================================================
//                        Copyright 2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A counter providing only operations meaningful for a
//!            counter, plus checking of the initial value, of overflow
//!            and underflow.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_igDqQSfWTOavMKrliVx0QKSbOMZ1k4kD
#define BREEZE_GUARD_igDqQSfWTOavMKrliVx0QKSbOMZ1k4kD

#include "breeze/top_level_namespace.hpp"
#include "breeze/operator/comparison.hpp"

namespace breeze_ns {

//      counter:
//      ========
//
//!     \copybrief counter.hpp
//!
//!     This template is a bit unusual, in that it performs checks via
//!     \c BREEZE_ASSERT() which are part of its contract (see e.g. the
//!     documentation of the \c ++ and \c \-- operator functions),
//!     whereas \c BREEZE_ASSERT() is normally used to check for \e
//!     precondition violations, only.
// ---------------------------------------------------------------------------
template< typename IntegralType >
class counter
    :   private comparison< counter< IntegralType > >
{
public:
    //!     Constructs a counter having internal value \c
    //!     IntegralType( 0 ).
    // -----------------------------------------------------------------------
                        counter() ;

    //!     Constructs a counter with internal value \c n.
    //!
    //!     This constructor executes:
    //!
    //!     \code
    //!         BREEZE_ASSERT( n >= 0 ) ;
    //!     \endcode
    // -----------------------------------------------------------------------
    explicit            counter( IntegralType n ) ;

    //!     Pre-increments the counter. Can only be called on lvalues.
    //!
    //!
    //!     This functions checks for logical overflow (including if \c
    //!     IntegralType is unsigned), by executing:
    //!
    //!     \code
    //!         BREEZE_ASSERT(
    //!             value() < std::numeric_limits< IntegralType >::max() ) ;
    //!     \endcode
    //!
    //!     before incrementing the counter value.
    // -----------------------------------------------------------------------
    counter &           operator ++() & ;

    //!     Post-increments the counter. Can only be called on
    //!     lvalues.
    //!
    //!     Before incrementing the counter value, this function does
    //!     the same \c BREEZE_ASSERT() check as the pre-increment
    //!     function.
    // -----------------------------------------------------------------------
    counter             operator ++( int ) & ;

    //!     Pre-decrements the counter. Can only be called on lvalues.
    //!
    //!     This function checks for logical underflow (including if \c
    //!     IntegralType is unsigned), by executing:
    //!
    //!     \code
    //!         BREEZE_ASSERT( value() > 0 ) ;
    //!     \endcode
    //!
    //!     before decrementing the counter value.
    // -----------------------------------------------------------------------
    counter &           operator --() & ;

    //!     Post-decrements the counter. Can only be called on
    //!     lvalues.
    //!
    //!     Before decrementing the counter value, this function does
    //!     the same \c BREEZE_ASSERT() check as the pre-decrement
    //!     function.
    // -----------------------------------------------------------------------
    counter             operator --( int ) & ;

    //!     \return
    //!         The internal value of the counter.
    // -----------------------------------------------------------------------
    IntegralType        value() const ;

    //!     \return
    //!         \c true if an only if \c *this and \c other compare
    //!         equal (same internal value). Used by the base class.
    // -----------------------------------------------------------------------
    bool                is_equal( counter const & other ) const ;

    //!     Three-way comparison for counters. Used by the base class.
    // -----------------------------------------------------------------------
    int                 compare(  counter const & other ) const ;

private:
    IntegralType        m_count ;
} ;

}

#include "brz/counter.tpp"
#endif
