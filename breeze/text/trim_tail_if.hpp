// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A \c std::string trimmer accepting a predicate (tail of
//!            string).
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_yzz6bpfxotq2rsaIMxKu1Q0eC1AELUNX
#define BREEZE_GUARD_yzz6bpfxotq2rsaIMxKu1Q0eC1AELUNX

#include "breeze/top_level_namespace.hpp"
#include <string>

namespace breeze_ns {

//      trim_tail_if():
//      ===============
//
//!     \return
//!         A string obtained from \c s by removing all the trailing
//!         characters that satisfy the predicate \c pred.
// ---------------------------------------------------------------------------
template< typename Predicate >
std::string         trim_tail_if( std::string const & s, Predicate pred ) ;

}

#include "brz/trim_tail_if.tpp"
#endif
