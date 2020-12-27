// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Returns the ceiling of the quotient of two integers.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_je0uCwloDoKUCxUfOy7GHayNkITaDT0U
#define BREEZE_GUARD_je0uCwloDoKUCxUfOy7GHayNkITaDT0U

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//      ceiling_of_quotient():
//      ======================
//
//!     \copybrief ceiling_of_quotient.hpp
//!
//!     \par Type requirements
//!         \c Integer shall be an integral type or a cv-qualified
//!         version thereof.
//!
//!     \pre
//!          - b != 0
//!          - a / b does not overflow
//!
//!     \return
//!         The ceiling of the quotient between \c a and \c b.
//!
//!     Useful to answer questions such as: "How many octets do I need
//!     to store 20 bits?". Answer: <code>ceiling_of_quotient( 20, 8 )
//!     </code>.
// ---------------------------------------------------------------------------
template< typename Integer >
constexpr Integer   ceiling_of_quotient( Integer a, Integer b ) ;

}

#include "brz/ceiling_of_quotient.tpp"
#endif
