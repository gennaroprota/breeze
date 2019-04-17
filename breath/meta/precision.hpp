// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Metafunction yielding the \e precision of a type.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_crv8sfpsGwWru7Bdt9WKSehiAw6f4zgz
#define BREATH_GUARD_crv8sfpsGwWru7Bdt9WKSehiAw6f4zgz

#include "breath/meta/constant.hpp"

#include <limits>

namespace breath {
namespace meta {

//      precision:
//      ==========
//
//!     Metafunction yielding the \e precision of \c T, i.e. the number
//!     of bits it uses to represent values, excluding any sign and
//!     padding bits.
//!
//!     This is a meta::constant, with \c value_type \c int.
//!
//!     See also: meta::width and meta::padding.
//!
//!     \par Type requirements
//!         \c T shall be an integral type or a cv-qualified version
//!         thereof.
// ---------------------------------------------------------------------------
template< typename T >
class precision
    :   public constant< int, std::numeric_limits< T >::digits >
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
