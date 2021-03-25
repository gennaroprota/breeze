// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Base64 encoding.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_m83AHFwUQlZBwnHisbdZpcYHaazyL2sn
#define BREEZE_GUARD_m83AHFwUQlZBwnHisbdZpcYHaazyL2sn

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//      binary_to_base64():
//      ===================
//
//!     Converts a binary sequence to Base64. Conforms to RFC 3548,
//!     except that it allows to line-wrap the generated Base64 output
//!     (`wrap_column != 0`).
//!
//!     \pre
//!         wrap_column >= 0
//!
//!     \param begin
//!         Iterator to the first element of the binary sequence.
//!
//!     \param end
//!         One-past-the-end iterator in the binary sequence.
//!
//!     \param out
//!         Iterator to the first element of the Base64 output.
//!
//!     \param wrap_column
//!         Column where line-wrapping must occur in the generated
//!         output (<tt>0</tt> means "no wrapping").
// ---------------------------------------------------------------------------
template< typename InputIter, typename OutputIter >
void                binary_to_base64( InputIter begin, InputIter end,
                                      OutputIter out,
                                      int wrap_column = 0 ) ;

}

#include "brz/binary_to_base64.tpp"
#endif
