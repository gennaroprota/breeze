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

#ifndef BREEZE_GUARD_crv8sfpsGwWru7Bdt9WKSehiAw6f4zgz
#define BREEZE_GUARD_crv8sfpsGwWru7Bdt9WKSehiAw6f4zgz

#include "breeze/top_level_namespace.hpp"
#include "breeze/meta/constant.hpp"

#include <limits>

namespace breeze_ns {
namespace meta {

//      precision:
//      ==========
//
//!     \copybrief precision.hpp
//!
//!     The \e precision of \c T is the number of bits that \c T uses to
//!     represent values, excluding any sign and padding bits.
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
