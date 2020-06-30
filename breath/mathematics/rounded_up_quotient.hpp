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

#ifndef BREATH_GUARD_je0uCwloDoKUCxUfOy7GHayNkITaDT0U
#define BREATH_GUARD_je0uCwloDoKUCxUfOy7GHayNkITaDT0U

#include "breath/top_level_namespace.hpp"

namespace breath_ns {

//      rounded_up_quotient():
//      ======================
//
//!     \par Type requirements
//!         \c Integer shall be an integral type or a cv-qualified
//!         version thereof.
//!
//!     \pre
//!         b != 0
//!
//!     \return
//!         The ceiling of the quotient between \c a and \c b.
//!
//!     Useful to answer questions such as: "How many octets do I need
//!     to store 20 bits?". Answer: <code>rounded_up_quotient( 20, 8 )
//!     </code>.
// ---------------------------------------------------------------------------
template< typename Integer >
constexpr Integer   rounded_up_quotient( Integer a, Integer b ) noexcept ;

}

#include "brt/rounded_up_quotient.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
