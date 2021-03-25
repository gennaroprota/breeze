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

#ifndef BREEZE_GUARD_zRk6qVzrOdWWtkjYcUpuIkpnrRj8cg0q
#define BREEZE_GUARD_zRk6qVzrOdWWtkjYcUpuIkpnrRj8cg0q

#include "breeze/top_level_namespace.hpp"
#include "breeze/preprocessing/prevent_macro_expansion.hpp"
#include <stdexcept>
#include <string>

namespace breeze_ns {

//      entropy_source:
//      ===============
//
//!     \copybrief entropy_source.hpp
//!
//!     This class represents the system entropy source, for generating
//!     non-deterministic (i.e. non-pseudo-random) random numbers.
//!
//!     It is similar to `std::random_device` but predates it and is
//!     more portable. Differently from the standard version, it is not
//!     implemented on systems which don't have a usable
//!     non-deterministic source (but, as of writing this, there's no
//!     such a system among those supported by Breeze).
//!
//!     Also differently from `std::random_device`, this class does not
//!     have an `entropy()` member, as that would be of dubious
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
    //!     Deleted copy constructor.
    // -----------------------------------------------------------------------
                        entropy_source( entropy_source const & ) = delete ;

    //!     Deleted copy assignment operator.
    // -----------------------------------------------------------------------
    entropy_source &    operator =(     entropy_source const & ) = delete ;

    //!     The type of the random numbers returned (or, which is the
    //!     same, the return type of the `next()` function).
    //!
    //!     Guaranteed to be \e unsigned and different from `char` and
    //!     `unsigned char`.
    //!
    //!     Note that the system entropy source may work on a smaller
    //!     type (typically `unsigned char`); but we don't use `char` or
    //!     `unsigned char` on the interface because we don't want
    //!     things like
    //!
    //!     ```
    //!         std::cout << rnd.next() ;
    //!     ```
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
    //!         May throw an `entropy_source::exception` or a
    //!         `std::bad_alloc`.
    // -----------------------------------------------------------------------
                        entropy_source() ;

    //!     Calls `release()`, ignoring its return value, and destroys
    //!     the object.
    // -----------------------------------------------------------------------
                        ~entropy_source() noexcept ;

    //!     \return
    //!         A new random value, evenly distributed in <tt>[min(),
    //!         max()]</tt>.
    //!
    //!     \par Exceptions
    //!         An `entropy_source::exception` if the random number
    //!         cannot be generated.
    // -----------------------------------------------------------------------
    result_type         next() ;

    //!     \return
    //!         The minimum random number that can be emitted, i.e.
    //!         zero.
    // -----------------------------------------------------------------------
    static constexpr result_type
                        min BREEZE_PREVENT_MACRO_EXPANSION () noexcept ;

    //!     \return
    //!         The maximum random number that can be emitted
    //!         (typically, <tt>255</tt>).
    // -----------------------------------------------------------------------
    static constexpr result_type
                        max BREEZE_PREVENT_MACRO_EXPANSION () noexcept ;

    //!     The same as `next()`.
    // -----------------------------------------------------------------------
    result_type         operator ()() ;

    //!     \return
    //!         A new random value in the range <tt>[min(),
    //!         maximum]</tt>.
    //!
    //!     \pre
    //!         maximum <= max()
    // -----------------------------------------------------------------------
    result_type         operator ()( result_type maximum ) ;

    //!     \return
    //!         A new random value in the range <tt>[minimum, maximum]
    //!         </tt>.
    //!
    //!     \pre
    //!         minimum <= maximum
    //!         maximum - minimum <= max()
    // -----------------------------------------------------------------------
    result_type         operator ()( result_type minimum,
                                     result_type maximum ) ;

    //!     Releases the system resource(s) associated with this object
    //!     (usually a file or a handle).
    //!
    //!     This function is called by the destructor, but calling it
    //!     manually allows checking for errors.
    //!
    //!     \return
    //!         `true` if and only if the resource(s) were successfully
    //!         released.
    //!
    //!     \par Exceptions
    //!         none (reports via its return value)
    //!
    //!     \note
    //!         This function may be called multiple times. After
    //!         calling `release()`, the only functions that can be
    //!         called on the object are `release()` and the destructor.
    // -----------------------------------------------------------------------
    bool                release() noexcept ;

private:
    class               impl ;
    impl * const        m_impl ;
} ;

//!     \brief  The type of exceptions thrown by the members of
//!             `entropy_source`.
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
    //!     string as `what()` message.
    // -----------------------------------------------------------------------
    explicit            exception( std::string const & msg ) ;
} ;

}

#include "brz/entropy_source.ipp"
#endif
