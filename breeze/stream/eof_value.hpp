// ===========================================================================
//                        Copyright 2011 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A replacement for `EOF` and `char_traits::eof()`.
//!
//!
//!     A convenience source file to separate out the crazy \#includes
//!     required for using `EOF` or `char_traits<...>::eof()`:
//!
//!       1. the former would require including `<stdio.h>` or
//!          `<cstdio>`
//!       2. the latter would require `<string>`
//!
//!     Both choices are IMHO particularly annoying for maintenance and
//!     code review: any reader of the code would probably wonder, for
//!     (1), why you include `<cstdio>` if you are using C++ streams
//!     (and not stdio); and, for (2), why you include `<string>` even
//!     where there's no usage of `std::string`.
//!
//!     The root of the issue is the poor header partitioning of the
//!     standard library but we can't do anything about that. We can,
//!     however, separate things out so that the relevant #includes are
//!     insulated. Which is the only real purpose of this facility.
//!
//      NOTE: there's no .tpp file, here; it seemed just overkill. Also,
//      it seemed natural to add an is_eof_value(), since using
//      eq_int_type would still require #including the <string> header.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_9qsz7UnvkOIvyedOe6ND5qSGfNeCMIU0
#define BREEZE_GUARD_9qsz7UnvkOIvyedOe6ND5qSGfNeCMIU0

#include "breeze/top_level_namespace.hpp"
#include <string>

namespace breeze_ns {

//      eof_value():
//      ============
//
//!     \return
//!         The end-of-file value for the given `Stream`.
// ---------------------------------------------------------------------------
template< typename Stream >
typename Stream::int_type
eof_value( Stream const & )
{
    return Stream::traits_type::eof() ;
}

//      is_eof_value():
//      ===============
//
//!     \return
//!         Whether `x` equals the eof value for the `Stream` given as
//!         the second argument.
// ---------------------------------------------------------------------------
template< typename Stream >
bool
is_eof_value( typename Stream::int_type x, Stream const & )
{
    return Stream::traits_type::eq_int_type( x,
            Stream::traits_type::eof() ) ;
}

}

#endif
