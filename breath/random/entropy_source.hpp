// ===========================================================================
//                     Copyright 2008-2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Represents the system entropy source (random numbers).
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_zRk6qVzrOdWWtkjYcUpuIkpnrRj8cg0q
#define BREATH_GUARD_zRk6qVzrOdWWtkjYcUpuIkpnrRj8cg0q

#include "breath/idiom/declare_non_copyable.hpp"
#include "breath/diagnostics/exception.hpp"
#include "breath/preprocessing/prevent_macro_expansion.hpp"
#include <string>

namespace breath {

//!     \note
//!         This class is designed to be usable with random_shuffle
//!         and shuffle. (This is, BTW, why it has members with the
//!         names "min" and "max", which I generally avoid, given
//!         how many sources define them as macro names.)
//!
//!     It satisfies the requirements of a "uniform random number
//!     generator".
//!
//!     What about the complexity of g()? [gps]
//!
// ---------------------------------------------------------------------------
class entropy_source
{
public:
    BREATH_DECLARE_NON_COPYABLE( entropy_source )

    //!     The type of the random numbers returned (\c next()
    //!     function).
    //!
    //!     Guaranteed to be \e unsigned and different from \c char and
    //!     <code>unsigned char</code>.
    //!
    //!     Note that the system entropy source may work on a smaller
    //!     type (typically <code>unsigned char</code>); but we don't
    //!     use \c char or <code>unsigned char</code> on the interface
    //!     because we don't want things such as
    //!
    //!     <code>
    //!         std::cout << rnd.next()
    //!     </code>
    //!
    //!     to output a character instead of a number.
    // -----------------------------------------------------------------------
    typedef unsigned int
                        result_type ;

    class               exception ;

    //!     Acquires the resource(s) necessary to generate random
    //!     numbers. May throw an \c entropy_source::exception or a
    //!     \c std::bad_alloc.
    // -----------------------------------------------------------------------
                        entropy_source() ;

    //!     Calls \c release() ignoring its return value, and destroys
    //!     the object.
    // -----------------------------------------------------------------------
                        ~entropy_source() noexcept ;

    //!     \return
    //!         A new random value, evenly distributed in [min(),
    //!         max()]. Each call gives, with overwhelming probability,
    //!         a different value.
    // -----------------------------------------------------------------------
    result_type         next() ;

    //!     \return
    //!         The minimum random number that can be emitted, i.e.
    //!         zero.
    // -----------------------------------------------------------------------
    result_type         min BREATH_PREVENT_MACRO_EXPANSION () const noexcept ;

    //!     \return
    //!         The maximum random number that can be emitted.
    // -----------------------------------------------------------------------
    result_type         max BREATH_PREVENT_MACRO_EXPANSION () const noexcept ;

    //!     \todo:
    //!         define entropy()??? It should be 8 for /dev/random...
    //!         what about the CryptoAPI?
    // -----------------------------------------------------------------------


    //!     \return
    //!         A new random value: the same as \c next().
    // -----------------------------------------------------------------------
    result_type         operator ()() ;

    //!     \return
    //!         A new random value in the range <code>[min(), maximum]
    //!         </code>.
    // -----------------------------------------------------------------------
    result_type         operator ()( result_type maximum ) ;

    //!     Releases the system resource(s) associated with this
    //!     object (usually a file or a handle).
    //!
    //!     \return
    //!         \c true if and only if the resource(s) were successfully
    //!         released.
    //!
    //!     Throws: nothing (reports via its return value)
    //!
    //!     \warning
    //!         You cannot reattempt a release if it already succeeded.
    // -----------------------------------------------------------------------
    bool                release() noexcept ;

private:
    class               impl ;
    impl * const        m_impl ;
} ;

//!     \brief  The type of exceptions thrown by \c entropy_source's
//!             members.
// ---------------------------------------------------------------------------
class entropy_source::exception
    :   public virtual breath::exception
{
public:
    //! \cond
    [[ noreturn ]] static void
                        raise( std::string const & message ) ;
    //! \endcond

    //!     Constructs an entropy_source::exception with the given
    //!     string as \c what() message. The string returned by \c
    //!     what() could be truncated.
    // -----------------------------------------------------------------------
    explicit            exception( std::string const & msg ) noexcept ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
