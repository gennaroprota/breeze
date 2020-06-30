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

#ifndef BREATH_GUARD_DjUmH0WQBIis1gQMNQWYhB7KQHMzHYQQ
#define BREATH_GUARD_DjUmH0WQBIis1gQMNQWYhB7KQHMzHYQQ

#include "breath/top_level_namespace.hpp"
#include "breath/meta/constant.hpp"

namespace breath_ns {
namespace meta {

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

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
