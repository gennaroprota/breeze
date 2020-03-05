// ===========================================================================
//                     Copyright 2006-2010 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A basic assertion facility.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_k8gjtzbloTDgF7FRM6AWORSGsE1IHkXq
#define BREATH_GUARD_k8gjtzbloTDgF7FRM6AWORSGsE1IHkXq

namespace breath {
//! \cond
namespace assert_private {

template< typename T >
void                block_non_bools( T ) = delete ;

inline constexpr bool
block_non_bools( bool b )
{
    return b ;
}

[[ noreturn ]] void fire( char const * message,
                          char const * file_name,
                          unsigned long line_number ) noexcept ;

}
//! \endcond
}

//      BREATH_ASSERT():
//      ================
//
//!     \hideinitializer
//!
//!     %BREATH_ASSERT() is a simple runtime assertion facility.
//!     Differently from the standard \c assert(), it has always the
//!     same expansion (regardless of \c NDEBUG).
//!
//!     The code <code>BREATH_ASSERT( expr )</code> expands to an
//!     expression, let's call it \c assert_expr, which contains \c expr
//!     as a sub-expression.
//!
//!     \c expr must have type bool or cv-qualified bool (this is a
//!     change from the past: we used to accept anything implicitly or
//!     explicitly convertible to bool; which means that e.g. \c expr
//!     could be the name of a \c std::optional---we think the new
//!     specification is safer).
//!
//!     When \c assert_expr is evaluated: if \c expr is \c false, an
//!     assertion is triggered; if it is \c true, the evaluation of \c
//!     assert_expr has no effects besides the evaluation of the
//!     sub-expression \c expr.
//!
//!     In this context, "triggering an assertion" means writing
//!     information related to the specific macro invocation (e.g. line
//!     number and source file name) to \c std::cerr, then calling \c
//!     std::abort().
//!
//!     Rationale
//!     ---------
//!
//!     It has become "common practice" to define the macro \c NDEBUG
//!     when compiling the "release" version of code. Many IDEs do so
//!     silently. In fact, \c NDEBUG (or a logical complement of it,
//!     such as \c _DEBUG) has become the macro which is usually checked
//!     for by your library code to know which version of it
//!     (release/debug) you want to link with.
//!
//!     We believe, though, that assertions must be left on in the
//!     release version of the product. So we wanted an assert macro
//!     decoupled from \c NDEBUG. (Thinking of it, there has been a
//!     fatal misunderstanding: the C committee thought of a macro to
//!     enable/disable assertions, but alas named it "NDEBUG", which
//!     suggests "no debug". And that's the meaning everyone seems to
//!     have assigned to it. Had they called it e.g. "NASSERT" all this
//!     wouldn't probably have happened.)
// ---------------------------------------------------------------------------
#define BREATH_ASSERT( expression )                                            \
    (                                                                          \
        breath::assert_private::block_non_bools( expression )                  \
            ? static_cast< void >( 0 )                                         \
            : breath::assert_private::fire( # expression, __FILE__, __LINE__ ) \
    )                                                                       /**/

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
