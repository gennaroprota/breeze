// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A std::string trimmer accepting a predicate (head of
//!            string).
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_h57CrFESUSfZFQj2EBQob5O94l5AybNU
#define BREATH_GUARD_h57CrFESUSfZFQj2EBQob5O94l5AybNU

#include <string>

namespace breath {

//      trim_head_if():
//      ===============
//
//!     \return
//!         A string obtained from \c str by removing all the leading
//!         characters that satisfy the predicate \c pred.
// ---------------------------------------------------------------------------
template< typename Predicate >
std::string         trim_head_if( std::string const & str, Predicate pred ) ;

}

#include "brt/trim_head_if.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
