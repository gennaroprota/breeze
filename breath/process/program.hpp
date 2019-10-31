// ===========================================================================
//                     Copyright 2010-2019 Gennaro Prota
//                      Copyright 1997-2000 James Kanze
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A singleton class to manage the overall status of the
//!            program and its termination.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_1kA1ToNG1qsz9KwlXD9MfVvhaHxMym5b
#define BREATH_GUARD_1kA1ToNG1qsz9KwlXD9MfVvhaHxMym5b

#include "breath/idiom/declare_non_copyable.hpp"
#include "breath/idiom/maybe.hpp"
#include "breath/process/exit_code.hpp"
#include <string>

namespace breath {

//      program:
//      ========
//
//!     Manager of the overall program status and termination.
// ---------------------------------------------------------------------------
class program
{
public:
    BREATH_DECLARE_NON_COPYABLE( program )

private:
                        program() noexcept ;
                        ~program() noexcept = default ;

public:
    //!     The gravity of an error.
    //
    //      NOTE: keep the enumeration in sync with the exit_codes[]
    //            array in the implementation file.
    // -----------------------------------------------------------------------
    enum gravity
    {
        comment = 0, // equivalent to success
        warning,
        error,
        fatal,
        internal
    } ;

    static program &    instance() noexcept ;

    //!     \return
    //!         An integer to be passed to \c std::exit() or returned
    //!         from \c main(). This corresponds to the most severe
    //!         error reported by client code to the \c program class
    //!         through the \c declare_error() member function.
    //!
    //!     If the system supports it, the various gravities will be
    //!     distinguished in the exit code; if not, all you get is
    //!     \c EXIT_SUCCESS or \c EXIT_FAILURE.
    //!
    //!     Important: this function also flushes \c std::cout, and
    //!     calls \c declare_error() if the flush fails (for this
    //!     reason, it is not const).
    // -----------------------------------------------------------------------
    int                 exit_code() ;

    //!     Sets the program name from the arguments to main, if they
    //!     contain a non-empty name (<tt>argc > 0 && argv[ 0 ][ 0 ]
    //!     != '\0'</tt>). Otherwise does nothing.
    //!
    //!     If the name is set, any leading path is stripped.
    //!
    //!     \pre
    //!         name was not set before
    //!
    //!     \post
    //!         \e none
    // -----------------------------------------------------------------------
    void                set_name( int argc, char const * const * argv ) ;

    //!     Sets the program name from the arguments to main, if they
    //!     contain a non-empty name; otherwise sets it from \c
    //!     fallback.
    //!
    //!     In any case, any leading path is stripped.
    //!
    //!     \pre
    //!         <tt>! fallback.empty()</tt> and name was not
    //!         set before
    //!
    //!     \post
    //!         <tt>name().is_valid()</tt>
    // -----------------------------------------------------------------------
    void                set_name( int argc, char const * const * argv,
                                  std::string const & fallback ) ;

    //!     Sets the program name to \c name, with any leading path
    //!     stripped.
    //!
    //!     \pre
    //!         <tt>! name.empty()</tt> and name was not set
    //!          before
    //!
    //!     \post
    //!         <tt>name().is_valid()</tt>
    // -----------------------------------------------------------------------
    void                set_name( std::string const & name ) ;

    //!     \return
    //!         The program name set by \c set_name().
    // -----------------------------------------------------------------------
    maybe< std::string >
                        name() const ;

    //!     Declares a program error.
    //!
    //!     \param g
    //!         The gravity of the error. If the gravity is higher
    //!         than any seen previously, it is saved to be used in
    //!         \c exit_code().
    //!
    //!     If the gravity is \c fatal or higher, this will also
    //!     terminate the program by calling \c terminate() (gravity
    //!     == \c fatal) or \c std::abort() (gravity == \c internal).
    // -----------------------------------------------------------------------
    void                declare_error( gravity g ) ;

    //!     Triggers the termination of the program with the exit
    //!     code which corresponds to the maximum value seen until
    //!     now. This function calls the function specified by
    //!     set_terminate_handler(), if set_terminate_handler() has
    //!     been called; otherwise, it calls \c std::exit().
    // -----------------------------------------------------------------------
    [[noreturn]] void   terminate() ;

    //!     Sets \c *user_function as the "terminate handler", i.e. as
    //!     the function which is called, with the exit code as an
    //!     argument, if there is a fatal error or if the user calls
    //!     terminate(). This makes it possible for the user to avoid
    //!     calling the default terminate handler, which is \c std::exit
    //!     (and thus to avoid \e not calling destructors of local
    //!     objects), for example, by raising an exception with the
    //!     argument, having taken the precaution to encapsulate the
    //!     entire contents of \c main() with:
    //!
    //!     \code
    //!         try {
    //!             breath::program::instance().set_terminate_handler(
    //!                                             raise_int_exception ) ;
    //!             // ...
    //!         } catch ( int exit_code ) {
    //!             return exit_code ;
    //!         }
    //!     \endcode
    //!
    //!     \note
    //!         The terminate handler should not return, or \c
    //!         std::abort() will be called immediately after.
    // -----------------------------------------------------------------------
    void                set_terminate_handler( void (*user_function)( int ) ) ;

private:
    void                do_set_name( std::string const & name ) ;

    gravity             m_max_gravity ;
    maybe< std::string >
                        m_program_name ;
    void (*             m_terminate_handler)( int ) ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
