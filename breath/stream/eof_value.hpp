// ===========================================================================
//                        Copyright 2011 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A replacement for \c EOF and \c char_traits::eof().
//!
//!
//!     A convenience source file to separate out the crazy \#includes
//!     required for using \c EOF or \c char_traits<...>::eof():
//!
//!       1. the former would require including \c <stdio.h> or \c
//!          <cstdio>
//!       2. the latter would require \c <string>
//!
//!     Both choices are IMHO particularly annoying for maintenance
//!     and code review: any reader of the code would probably wonder,
//!     for (1), why you include \c <cstdio> if you are using C++
//!     streams (and not stdio); and, for (2), why you include \c
//!     <string> even where there's no usage of \c std::string.
//!
//!     The root of the issue is the poor header partitioning of the
//!     standard library but we can't do anything about that. We can,
//!     however, separate things out so that the relevant #includes
//!     are insulated. Which is the only real purpose of this
//!     facility.
//!
//      NOTE: there's no .tpp file, here; it seemed just overkill.
//            Also, it seemed natural to add an is_eof_value(), since
//            using eq_int_type would still require #including the
//            <string> header.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_9qsz7UnvkOIvyedOe6ND5qSGfNeCMIU0
#define BREATH_GUARD_9qsz7UnvkOIvyedOe6ND5qSGfNeCMIU0

#include <string>

namespace breath {

//      eof_value():
//      ============
//
//!     \return
//!         The end-of-file value for the given \c Stream.
// -------------------------------------------------------------------------
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
//!         Whether \c x equals the eof value for the \c Stream given as
//!         the second argument.
// -------------------------------------------------------------------------
template< typename Stream >
bool
is_eof_value( typename Stream::int_type x, Stream const & )
{
    return Stream::traits_type::eq_int_type( x,
            Stream::traits_type::eof() ) ;
}

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
