// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Metafunction yielding the successor of another constant.
//!
//!     \todo: document behavior in case of overflow
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_DjUmH0WQBIis1gQMNQWYhB7KQHMzHYQQ
#define BREEZE_GUARD_DjUmH0WQBIis1gQMNQWYhB7KQHMzHYQQ

#include "breeze/top_level_namespace.hpp"
#include "breeze/meta/constant.hpp"

namespace breeze_ns {
namespace meta {

//      successor:
//      ==========
//
//!     \brief
//!         A meta::constant with the same \c value_type as \c T and \c
//!         value equal to <code>T::value + 1</code>.
// ---------------------------------------------------------------------------
template< typename T >
class successor
    :   public constant<
                        typename T::value_type
                        ,        T::value + 1
                       >
{
} ;

}
}

#endif
