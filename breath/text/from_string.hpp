// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Returns an object given its textual representation.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_Q6sxk1RUMey9fbjLvtacucg61F39I6ob
#define BREATH_GUARD_Q6sxk1RUMey9fbjLvtacucg61F39I6ob

#include "breath/top_level_namespace.hpp"
#include "breath/idiom/maybe.hpp"
#include <string>

namespace breath_ns {

//!     \par Type requirements
//!         \c T shall be \c DefaultConstructible and \c
//!         MoveConstructible. Furthermore it shall be \c input \c
//!         streamable from a \c std::istream, meaning that an <code>
//!         operator &gt;&gt;()</code> function may be called that takes
//!         an instance of \c std::istream as first argument and an
//!         instance of \c T as second argument.
// ---------------------------------------------------------------------------
template< typename T >
maybe< T >          from_string( std::string const & s ) ;

//!     \return
//!         An (always valid) \c maybe object containing a string which
//!         compares equal to \c s.
//!
//!     \note
//!         This specialization is not just an optimization: it ensures
//!         that e.g. " test " converts to " test " and not "test".
// ---------------------------------------------------------------------------
template<>
maybe< std::string> from_string< std::string >( std::string const & s ) ;

}

#include "brt/from_string.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
