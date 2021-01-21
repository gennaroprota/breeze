// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Metafunction yielding the \e width of a type.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_KvNAPbTCTNbIqTMjUCtxwBFR3ipIdp2y
#define BREEZE_GUARD_KvNAPbTCTNbIqTMjUCtxwBFR3ipIdp2y

#include "breeze/top_level_namespace.hpp"
#include "breeze/meta/has_sign.hpp"
#include "breeze/meta/precision.hpp"

namespace breeze_ns {
namespace meta {

//      width:
//      ======
//
//!     \copybrief width.hpp
//!
//!     The \e width of \c T is the number of bits that \c T uses to
//!     represent values, including any sign but excluding any padding
//!     bits.
//!
//!     This is a meta::constant, with \c value_type \c int.
//!
//!     See also: meta::precision and meta::padding.
//!
//!     \par Type requirements
//!
//!         \c T shall be an integral type or a cv-qualified version
//!         thereof.
// ---------------------------------------------------------------------------
template< typename T >
class width
    : public constant< int, has_sign< T >::value
                                ? precision< T >::value + 1
                                : precision< T >::value >
{
} ;

}
}

#endif
