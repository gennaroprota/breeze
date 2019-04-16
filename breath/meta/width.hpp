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
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_KvNAPbTCTNbIqTMjUCtxwBFR3ipIdp2y
#define BREATH_GUARD_KvNAPbTCTNbIqTMjUCtxwBFR3ipIdp2y

#include "breath/meta/has_sign.hpp"
#include "breath/meta/precision.hpp"
#include "breath/meta/select.hpp"
#include "breath/meta/successor.hpp"

namespace breath {
namespace meta {

//      width:
//      ======
//
//!     Metafunction yielding the \e width of \c T, i.e. the number of
//!     bits it uses to represent values, including any sign but
//!     excluding any padding bits.
//!
//!     This is a meta::constant, with \c value_type \c int.
//!
//!     See also: meta::precision and meta::padding.
//!
//!     \par Type requirements
//!         \c T shall be an integral type or a cv-qualified version
//!         thereof.
// -------------------------------------------------------------------------
template< typename T >
class width
    :   public select< has_sign< T >,
                       successor< precision < T > >,
                       precision < T >
                     >::type
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
