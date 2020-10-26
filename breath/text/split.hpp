// ===========================================================================
//                     Copyright 2011-2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Splits a \c std::string into a \c std::vector of strings.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_V50EdenEkFY3WA0JCnjok8aia0tACes8
#define BREATH_GUARD_V50EdenEkFY3WA0JCnjok8aia0tACes8

#include "breath/top_level_namespace.hpp"
#include <string>
#include <vector>

namespace breath_ns {

//      split():
//      ========
//
//!     \return
//!         A vector of strings obtained by splitting \c s at each
//!         character present in \c separators, in order.
//!
//!         Consecutive separators, or separators as first or last
//!         character in \c s, lead to an empty string in the resulting
//!         vector. The size of the vector is always 1 plus the number
//!         of separators in \c s.
//!
//!     \note
//!         This should probably use \c set_of_chars.
// ---------------------------------------------------------------------------
std::vector< std::string >
                    split( std::string const & s,
                           std::string const & separators ) ;

//      split_if():
//      ===========
//
//!     \return
//!         A vector of strings obtained by splitting \c s at each
//!         character which satisfies the predicate \c pred, in order.
//!
//!         A character which satisfies \c pred is called a \e separator
//!         in the following.
//!
//!         Consecutive separators, or separators as first or last
//!         character in \c s, lead to an empty string in the resulting
//!         vector. The size of the vector is always 1 plus the number
//!         of separators in \c s.
//!
//!     \note
//!         This should probably use \c set_of_chars.
// ---------------------------------------------------------------------------
template< typename UnaryPredicate >
std::vector< std::string >
                    split_if( std::string const & s,
                              UnaryPredicate      pred ) ;

}

#include "brt/split.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
