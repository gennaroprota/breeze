// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief The integer part of the logarithm, to base 2, of its
//!            argument.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_Kym3FA1ex9fw5x3d1rVgY686BX4YRKvw
#define BREATH_GUARD_Kym3FA1ex9fw5x3d1rVgY686BX4YRKvw

#include "breath/top_level_namespace.hpp"
#include <cstdint>

namespace breath_ns {

//      integer_log2():
//      ===============
//
//      \return
//!         The behavior is undefined if <code>x <= 0</code> (and might
//!         result in an assertion failure). Otherwise the function
//!         returns the integer part of the logarithm, base 2, of its
//!         argument.
//!
//!     \note
//!         This \c constexpr function supersedes \c meta::integer_log2,
//!         which is declared deprecated.
//!     \note
//!         This function does not compile with Visual C++ 2015 because
//!         the compiler does not yet implement \c constexpr functions
//!         as generalized in C++14.
// ---------------------------------------------------------------------------
constexpr int       integer_log2( std::intmax_t x ) noexcept ;

}

#include "brt/integer_log2.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
