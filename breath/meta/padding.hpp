// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Metafunction yielding the number of \e padding bits of a
//!            type.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_t29jfKYZ9OI7vFPLyiSoFtL9Jw9Lntnr
#define BREATH_GUARD_t29jfKYZ9OI7vFPLyiSoFtL9Jw9Lntnr

#include "breath/meta/width.hpp"

namespace breath {
namespace meta {

//      padding:
//      ========
//
//!     Metafunction yielding the number of \e padding bits of \c T.
//!
//!     This is a meta::constant, with \c value_type \c int.
//!
//!     See also: meta::precision and meta::width.
//!
//!     \par Type requirements
//!         \c T shall be an integral type or a cv-qualified version
//!         thereof.
// -------------------------------------------------------------------------
template< typename T >
class padding
    :   public constant< int,
                         width< unsigned char >::value * sizeof( T ) -
                         width< T             >::value
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
