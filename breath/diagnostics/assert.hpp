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
//!     %BREATH_ASSERT() is the simplest runtime assertion facility in
//!     the Breath collection. Differently from the standard \c
//!     assert(), it has always the same expansion (regardless of \c
//!     NDEBUG).
//!
//!     The code <code>BREATH_ASSERT( expr )</code> expands to an
//!     expression. When that expression is evaluated: first, if \c expr
//!     is not convertible to \c bool the program is ill-formed;
//!     otherwise, an assertion is triggered if the result of that
//!     conversion is \c false. If the result is \c true, the evaluation
//!     has no effects besides the conversion to \c bool itself.
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
#define BREATH_ASSERT( expression )                                          \
    (                                                                        \
        ( expression )                                                       \
          ? static_cast< void >( 0 )                                         \
          : breath::assert_private::fire( # expression, __FILE__, __LINE__ ) \
    )                                                                     /**/

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
