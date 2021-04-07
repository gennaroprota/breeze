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
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_t29jfKYZ9OI7vFPLyiSoFtL9Jw9Lntnr
#define BREEZE_GUARD_t29jfKYZ9OI7vFPLyiSoFtL9Jw9Lntnr

#include "breeze/top_level_namespace.hpp"
#include "breeze/meta/width.hpp"

namespace breeze_ns {

//      padding:
//      ========
//
//!     \brief
//!         Metafunction yielding the number of \e padding bits of a
//!         type.
//!
//!     This is a `constant`, with `value_type` `int`.
//!
//!     \see
//!         precision and width.
//!
//!     \par Type requirements
//!         `T` shall be an integral type or a cv-qualified version
//!         thereof.
// ---------------------------------------------------------------------------
template< typename T >
class padding
    :   public constant< int,
                         width< unsigned char >::value * sizeof( T ) -
                         width< T             >::value
                       >
{
} ;

}

#endif
