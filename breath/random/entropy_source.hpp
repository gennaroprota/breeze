// ===========================================================================
//                     Copyright 2008-2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief The system entropy source (random numbers).
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_zRk6qVzrOdWWtkjYcUpuIkpnrRj8cg0q
#define BREATH_GUARD_zRk6qVzrOdWWtkjYcUpuIkpnrRj8cg0q

#include "breath/top_level_namespace.hpp"
#include "breath/preprocessing/prevent_macro_expansion.hpp"
#include <stdexcept>
#include <string>

namespace breath_ns {

//      entropy_source:
//      ===============
//
//!     \copybrief entropy_source.hpp
//!
//!     This class represents the system entropy source, for generating
//!     non-deterministic (i.e. non-pseudo-random) random numbers.
//!
//!     It is similar to \c std::random_device but predates it and is
//!     more portable. Differently from the standard version, it is not
//!     implemented on systems which don't have a usable
//!     non-deterministic source (but, as of writing this, there's no
//!     such a system among those supported by Breath).
//!
//!     Also differently from \c std::random_device, this class does not
//!     have an \c entropy() member, as that would be of dubious
//!     usefulness (see e.g.
//!     <https://codingnest.com/generating-random-numbers-using-c-standard-library-the-problems/>).
//!
//!     \note
//!         This class is designed to satisfy the requirements of a <tt>
//!         uniform random number generator</tt> (C++11,
//!         [rand.req.urng]), except that, to be honest, I don't know
//!         what the complexity of the function call operator is. (These
//!         requirements are, by the way, why it has members named "min"
//!         and "max", which I generally avoid, given that many sources
//!         define homonym macros.)
// ---------------------------------------------------------------------------
class entropy_source
{
public:
    //!\{
    //!     Copy members are deleted.
    // -----------------------------------------------------------------------
                        entropy_source( entropy_source const & ) = delete ;
    entropy_source &    operator =(     entropy_source const & ) = delete ;
    //!\}

    //!     The type of the random numbers returned (or, which is the
    //!     same, the return type of the \c next() function).
    //!
    //!     Guaranteed to be \e unsigned and different from \c char and
    //!     <code>unsigned char</code>.
    //!
    //!     Note that the system entropy source may work on a smaller
    //!     type (typically <code>unsigned char</code>); but we don't
    //!     use \c char or <code>unsigned char</code> on the interface
    //!     because we don't want things like
    //!
    //!     \code
    //!         std::cout << rnd.next() ;
    //!     \endcode
    //!
    //!     to output a character instead of a number.
    // -----------------------------------------------------------------------
    typedef unsigned int
                        result_type ;

    class               exception ;

    //!     Acquires the resource(s) necessary to generate random
    //!     numbers.
    //!
    //!     \par Exceptions
    //!         May throw an \c entropy_source::exception or a \c
    //!         std::bad_alloc.
    // -----------------------------------------------------------------------
                        entropy_source() ;

    //!     Calls \c release(), ignoring its return value, and destroys
    //!     the object.
    // -----------------------------------------------------------------------
                        ~entropy_source() noexcept ;

    //!     \return
    //!         A new random value, evenly distributed in <tt>[min(),
    //!         max()]</tt>. Each call gives, with overwhelming
    //!         probability, a different value.
    //!
    //!     \par Exceptions
    //!         An \c entropy_source::exception if the random number
    //!         cannot be generated.
    // -----------------------------------------------------------------------
    result_type         next() ;

    //!     \return
    //!         The minimum random number that can be emitted, i.e.
    //!         zero.
    // -----------------------------------------------------------------------
    static constexpr result_type
                        min BREATH_PREVENT_MACRO_EXPANSION () noexcept ;

    //!     \return
    //!         The maximum random number that can be emitted
    //!         (typically, <tt>255</tt>).
    // -----------------------------------------------------------------------
    static constexpr result_type
                        max BREATH_PREVENT_MACRO_EXPANSION () noexcept ;

    //!     The same as \c next().
    // -----------------------------------------------------------------------
    result_type         operator ()() ;

    //!     \return
    //!         A new random value in the range <code>[min(), maximum]
    //!         </code>.
    // -----------------------------------------------------------------------
    result_type         operator ()( result_type maximum ) ;

    //!     Releases the system resource(s) associated with this object
    //!     (usually a file or a handle).
    //!
    //!     \return
    //!         \c true if and only if the resource(s) were successfully
    //!         released.
    //!
    //!     \par Exceptions
    //!         none (reports via its return value)
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
    :   public std::runtime_error
{
public:
    //!\cond implementation
    [[ noreturn ]] static void
                        raise( std::string const & message ) ;
    //!\endcond

    //!     Constructs an entropy_source::exception with the given
    //!     string as \c what() message.
    // -----------------------------------------------------------------------
    explicit            exception( std::string const & msg ) ;
} ;

}

#include "brt/entropy_source.ipp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
