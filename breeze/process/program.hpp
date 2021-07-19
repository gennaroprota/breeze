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

#ifndef BREEZE_GUARD_1kA1ToNG1qsz9KwlXD9MfVvhaHxMym5b
#define BREEZE_GUARD_1kA1ToNG1qsz9KwlXD9MfVvhaHxMym5b

#include "breeze/top_level_namespace.hpp"
#include "breeze/process/exit_code.hpp"
#include <string>

namespace breeze_ns {

//      get_program_name():
//      -------------------
//
//!     This function must be implemented by the user of the library and
//!     should, of course, return the program name. That name will be
//!     output together with any error message emitted by
//!     `program::declare_error()`, so that the source of the error is
//!     clear.
//!
//!     To implement this function, write:
//!
//!     ```
//!         namespace breeze_ns {
//!
//!         std::string
//!         get_program_name()
//!         {
//!             ...
//!         }
//!
//!         }
//!     ```
//!
//!     and not:
//!
//!     ```
//!         namespace breeze {  // <-- no
//!             ...
//!         }
//!     ```
// ---------------------------------------------------------------------------
std::string         get_program_name() ;


//      program:
//      ========
//
//!     \copybrief program.hpp
// ---------------------------------------------------------------------------
class program
{
public:
    //      gravity:
    //      --------
    //
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

    //!     Deleted copy constructor (this class is a singleton).
    // -----------------------------------------------------------------------
                        program(    program const & ) = delete ;

    //!     Deleted copy assignment operator (this class is a singleton).
    // -----------------------------------------------------------------------
    program &           operator =( program const & ) = delete ;

    //      instance():
    //      -----------
    //
    //!     \return
    //!         A reference to the one and only instance of the class.
    // -----------------------------------------------------------------------
    static program &    instance() noexcept ;

    //      declare_error():
    //      ----------------
    //
    //!     Declares a program error.
    //!
    //!     \param g
    //!         The gravity of the error. If the gravity is higher than
    //!         any seen previously, it is saved to be used in
    //!         `exit_code()`.
    //!
    //!     If the gravity is `fatal` or higher, this will also
    //!     terminate the program by calling `program::terminate()`
    //!     (when the gravity is `fatal`) or `std::abort()` (when it is
    //!     `internal`).
    // -----------------------------------------------------------------------
    void                declare_error( gravity g ) ;

    //      declare_error():
    //      ----------------
    //
    //      Outputs a message to `std::cerr` and declares a program
    //      error.
    //
    //      This function outputs `message` and the program name,
    //      followed by a newline, to `std::cerr`, then calls
    //      `declare_error( g )`.
    // -----------------------------------------------------------------------
    void            declare_error( gravity g, std::string const & message ) ;

    //      exit_code():
    //      ------------
    //
    //!     \return
    //!         An integer to be passed to `std::exit()` or returned
    //!         from `main()`. This corresponds to the most severe error
    //!         reported by client code to the `program` class through
    //!         the `declare_error()` member function.
    //!
    //!     If possible, the various gravities will be distinguished in
    //!     the exit code, but e.g. `warning` will be undistinguishable
    //!     from a success with no warnings on Windows and Unix (because
    //!     treating a distinct value as success would be too difficult
    //!     in a shell script); in the worst case, all you get is
    //!     `EXIT_SUCCESS` or `EXIT_FAILURE`.
    //!
    //!     <strong>Important</strong>: before anything else, this
    //!     function calls `std::cout.flush()`; then, if `std::cout` is
    //!     in a failed or bad state (because the flush failed or
    //!     because it already was in that state before the (failed)
    //!     flush attempt), calls `declare_error( error )` (for this
    //!     reason, it is not const). This is somewhat of a hack, but it
    //!     ensures that the exit code never indicates success if there
    //!     is an I/O error on `std::cout`, which means that, for
    //!     instance, if the usual shell idiom
    //!
    //!     ```
    //!         my_program file > tmp && mv tmp file
    //!     ```
    //!
    //!     is used and `std::cout` in `my_program` hits a disk full,
    //!     `file` won't be truncated.
    //!
    //!     Of course, the exit code is unaffected if `std::cout` isn't
    //!     used at all, which should be the case e.g. in a Windows GUI
    //!     application.
    // -----------------------------------------------------------------------
    int                 exit_code() ;

    //      terminate():
    //      ------------
    //
    //!     Triggers the termination of the program with the exit code
    //!     which corresponds to the maximum value seen until now. This
    //!     function calls the function specified by
    //!     set_terminate_handler(), if set_terminate_handler() has been
    //!     called; otherwise, it calls `std::exit()`.
    // -----------------------------------------------------------------------
    [[ noreturn ]] void terminate() ;

    //      set_terminate_handler():
    //      ------------------------
    //
    //!     Sets `*user_function` as the "terminate handler", i.e. as
    //!     the function which is called, with the exit code as an
    //!     argument, if there is a fatal error or if the user calls
    //!     `program::terminate()`. This makes it possible for the user
    //!     to avoid calling the default terminate handler, which is
    //!     `std::exit()` (and thus to avoid \e not calling destructors
    //!     of local objects), for example, by raising an exception with
    //!     the argument, having taken the precaution to encapsulate the
    //!     entire contents of `main()` with:
    //!
    //!     ```
    //!         try {
    //!             breeze::program::instance().set_terminate_handler(
    //!                                             raise_int_exception ) ;
    //!             // ...
    //!         } catch ( int exit_code ) {
    //!             return exit_code ;
    //!         }
    //!     ```
    //!
    //!     \note
    //!         The terminate handler should not return, or
    //!         `std::abort()` will be called immediately after.
    // -----------------------------------------------------------------------
    void                set_terminate_handler( void (*user_function)( int ) ) ;

private:
                        program() noexcept ;

    gravity             m_max_gravity ;
    void (*             m_terminate_handler)( int ) ;
} ;

}

#endif
