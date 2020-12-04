// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Metafunction yielding the predecessor of a type.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_UdGvvEgZV1WGbMzbsiKOg7UnnY910Qsa
#define BREEZE_GUARD_UdGvvEgZV1WGbMzbsiKOg7UnnY910Qsa

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {
namespace meta {

//      predecessor:
//      ============
//
//!     \brief
//!         A meta::constant with the same \c value_type as \c T and \c
//!         value equal to <code>T::value - 1</code>.
// ---------------------------------------------------------------------------
template< typename T >
class predecessor
    :   public constant<
                        typename T::value_type
                        ,        T::value - 1
                       >
{
} ;

}
}

#endif
