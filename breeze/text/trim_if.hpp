// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A `std::string` trimmer accepting a predicate.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_12722kkPcCmt1PN91r0QOwrcsntBhbKr
#define BREEZE_GUARD_12722kkPcCmt1PN91r0QOwrcsntBhbKr

#include "breeze/top_level_namespace.hpp"
#include <string>

namespace breeze_ns {

//      trim_if():
//      ==========
//
//!     \return
//!         A string obtained from `s` by removing all the leading and
//!         all the trailing characters that satisfy the predicate
//!         `pred`.
// ---------------------------------------------------------------------------
template< typename Predicate >
std::string         trim_if( std::string const & s, Predicate pred ) ;

}

#include "brz/trim_if.tpp"
#endif
