// ===========================================================================
//                     Copyright 2006-2010 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A basic, configurable assertion facility.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_k8gjtzbloTDgF7FRM6AWORSGsE1IHkXq
#define BREEZE_GUARD_k8gjtzbloTDgF7FRM6AWORSGsE1IHkXq

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//      assert_handler_type:
//      ====================
//
//!     The type of the function called by `BREEZE_ASSERT( expression )`
//!     if `expression` evaluates to `false`.
//!
//!     \param expression_text
//!         A pointer to a C-style string containing the text of
//!         `expression`.
//!
//!     \param file_name
//!         A pointer to a C-style string containing the name of the
//!         source file in which `BREEZE_ASSERT()` was invoked.
//!
//!     \param line_number
//!         The line number of the line in which `BREEZE_ASSERT()` was
//!         invoked.
// ---------------------------------------------------------------------------
typedef void      ( assert_handler_type )( char const * expression_text,
                                           char const * file_name,
                                           long line_number ) ;

//      set_assert_handler():
//      =====================
//
//!     Sets `*f` as the current "assert handler", i.e. as the function
//!     which is called by `BREEZE_ASSERT( expression )` if `expression`
//!     evaluates to `false`.
//!
//!     At program start up, the assert handler is
//!     `default_assert_handler()`.
//!
//!     \param f
//!         Pointer to the assert handler to set. The handler must not
//!         return: it must either terminate the program or emit an
//!         exception.
// ---------------------------------------------------------------------------
void                set_assert_handler( assert_handler_type * f ) ;

//      default_assert_handler():
//      =========================
//
//!     \brief The default assert handler for `BREEZE_ASSERT()`.
//!
//!     Writes the passed in arguments to `std::cerr`, then flushes
//!     `std::cerr`, then calls `std::abort()`.
//!
//!     \note
//!         Since this is a `noexcept` function, the program will
//!         terminate anyway if writing to `std::cerr` causes an
//!         exception to be emitted (this means that such an exception
//!         will not hide the programming error detected thanks to the
//!         assertion).
// ---------------------------------------------------------------------------
[[ noreturn ]] void
default_assert_handler( char const * expression_text,
                        char const * file_name,
                        long line_number ) noexcept ;

//!\cond implementation
namespace assert_private {

template< typename T >
void                block_non_bools( T ) = delete ;

inline constexpr bool
block_non_bools( bool b )
{
    return b ;
}

[[ noreturn ]] void fire( char const * expression_text,
                          char const * file_name,
                          long line_number ) ;

}
//!\endcond
}

//      BREEZE_ASSERT():
//      ================
//
//!     \hideinitializer
//!
//!     %BREEZE_ASSERT() is a simple runtime assertion facility.
//!     Differently from the standard `assert()`, it has always the same
//!     expansion (regardless of `NDEBUG`).
//!
//!     The code `BREEZE_ASSERT( expr )` expands to an expression, let's
//!     call it `assert_expr`, which contains `expr` as a
//!     sub-expression.
//!
//!     `expr` must have type bool or cv-qualified bool (this is a
//!     change from the past: we used to accept anything implicitly or
//!     explicitly convertible to bool; which means that e.g. `expr`
//!     could be the name of a `std::optional`---we think the new
//!     specification is safer).
//!
//!     When `assert_expr` is evaluated: if `expr` is `false`, an
//!     assertion is triggered; if it is `true`, the evaluation of
//!     `assert_expr` has no effects besides the evaluation of the
//!     sub-expression `expr`.
//!
//!     In this context, "triggering an assertion" means calling the
//!     current <i>assert handler</i> (see `set_assert_handler()`),
//!     passing it information related to the specific `BREEZE_ASSERT()`
//!     invocation (in particular, the text of the expression, the
//!     source file name and the line number).
//!
//!     \par Rationale
//!
//!     It has become common practice to define the macro `NDEBUG` when
//!     compiling the "release" versions of a product. Many IDEs do so
//!     silently. In fact, `NDEBUG` (or a logical complement of it, such
//!     as `_DEBUG`) has become the macro which is usually checked for
//!     by your library code to know which version of it (release/debug)
//!     you want to link with.
//!
//!     We believe, though, that assertions must be left on in the
//!     release builds. So we wanted an assert macro decoupled from
//!     `NDEBUG`. (Thinking of it, there has been a fatal
//!     misunderstanding: the C committee thought of a macro to
//!     enable/disable assertions, but alas named it "NDEBUG", which
//!     suggests "no debug". And that's the meaning everyone seems to
//!     have assigned to it. Had they called it e.g. "NASSERT" all this
//!     wouldn't probably have happened.)
//!
//!     About the possibility to throw an exception instead of
//!     terminating the program: while critical software will certainly
//!     need to terminate immediately in case of a programming error,
//!     there are applications which can continue: consider e.g. an
//!     editor, which could give the user a chance to save their work
//!     before aborting.
// ---------------------------------------------------------------------------
#define BREEZE_ASSERT( expression )                                            \
    (                                                                          \
        breeze::assert_private::block_non_bools( expression )                  \
            ? static_cast< void >( 0 )                                         \
            : breeze::assert_private::fire( # expression, __FILE__, __LINE__ ) \
    )                                                                       /**/

#endif
