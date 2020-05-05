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

namespace breath {

//      count_bits():
//      =============
//
//!     \return
//!         The number of on bits in the value \c t. \c T must be an
//!         unsigned integral type.
//!
//!     \warning
//!         [FUTURE] This function template will be removed in favor of
//!         \c std::popcount() when Breath will require C++20.
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
