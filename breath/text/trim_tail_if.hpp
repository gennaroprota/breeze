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

#ifndef BREATH_GUARD_yzz6bpfxotq2rsaIMxKu1Q0eC1AELUNX
#define BREATH_GUARD_yzz6bpfxotq2rsaIMxKu1Q0eC1AELUNX

#include "breath/top_level_namespace.hpp"
#include <string>

namespace breath_ns {

//      trim_tail_if():
//      ===============
//
//!     \return
//!         A string obtained from \c str by removing all the trailing
//!         characters that satisfy the predicate \c pred.
// ---------------------------------------------------------------------------
template< typename Predicate >
std::string         trim_tail_if( std::string const & str, Predicate pred ) ;

}

#include "brt/trim_tail_if.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
