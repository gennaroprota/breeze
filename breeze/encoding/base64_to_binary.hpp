// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Base64 decoding.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_ubEInhYBWjgftwkYlSFbSOFcFUILqJgK
#define BREEZE_GUARD_ubEInhYBWjgftwkYlSFbSOFcFUILqJgK

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//      base64_to_binary():
//      ===================
//
//!\brief
//!     Decodes a Base64 representation.
//!
//!     This function conforms to RFC 3548 with one exception: it allows
//!     \e newlines to appear anywhere in the input.
//!
//!     \par Exceptions
//!         A `std::runtime_error` on any invalid input character; this
//!         does not throw `std::logic_error` because, for input
//!         iterators, it's not possible for the user to check the input
//!         before passing it to us.
//!
//!     \param begin
//!         Iterator to the first element of the input (i.e. Base64)
//!         sequence.
//!
//!     \param end
//!         One-past-the-end iterator in the input sequence.
//!
//!     \param out
//!         Iterator to the first element of the output sequence
//!         (binary).
// ---------------------------------------------------------------------------
template< typename InputIter, typename OutputIter >
void                base64_to_binary( InputIter begin, InputIter end,
                                      OutputIter out ) ;

}

#include "brz/base64_to_binary.tpp"
#endif
