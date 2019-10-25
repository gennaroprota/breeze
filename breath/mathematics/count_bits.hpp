// ===========================================================================
//                        Copyright 2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A simple bit counter.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_D5dKoDqQ2v7QNXhW1F8zF0ZKijovEPgp
#define BREATH_GUARD_D5dKoDqQ2v7QNXhW1F8zF0ZKijovEPgp

#include <cstddef>

namespace breath {

//      count_bits():
//      =============
//
//!     \return
//!         The number of on bits in the value \c t. \c T must be an
//!         built-in integral type with no sign (\c bool is supported,
//!         too).
// ---------------------------------------------------------------------------
template< typename T >
constexpr int       count_bits( T t ) noexcept ;

}

#include "brt/count_bits.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
