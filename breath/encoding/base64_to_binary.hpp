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
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_ubEInhYBWjgftwkYlSFbSOFcFUILqJgK
#define BREATH_GUARD_ubEInhYBWjgftwkYlSFbSOFcFUILqJgK

namespace breath {

//      base64_to_binary():
//      ===================
//
//!     Decodes a Base64 representation.
//!
//!     This function conforms to RFC 3548 with one exception: it
//!     allows \e newlines to appear anywhere in the input.
//!
//!     \throw
//!         A \c breath::exception on any invalid input character.
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
// -------------------------------------------------------------------------
template< typename InputIter, typename OutputIter >
void                base64_to_binary( InputIter begin, InputIter end,
                                      OutputIter out ) ;

}

#include "brt/base64_to_binary.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
