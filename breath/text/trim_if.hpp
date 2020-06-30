// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A \c std::string trimmer accepting a predicate.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_12722kkPcCmt1PN91r0QOwrcsntBhbKr
#define BREATH_GUARD_12722kkPcCmt1PN91r0QOwrcsntBhbKr

#include "breath/top_level_namespace.hpp"
#include <string>

namespace breath_ns {

//      trim_if():
//      ==========
//
//!     \return
//!         A string obtained from \c str by removing all the leading
//!         and all the trailing characters that satisfy the predicate
//!         \c pred.
// ---------------------------------------------------------------------------
template< typename Predicate >
std::string         trim_if( std::string const & str, Predicate pred ) ;

}

#include "brt/trim_if.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
