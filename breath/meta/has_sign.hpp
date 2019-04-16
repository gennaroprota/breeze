// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Returns whether a type accepts negative values.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_hGv2WKy8LgUcETfMmcRpTRLRUQlhUJSH
#define BREATH_GUARD_hGv2WKy8LgUcETfMmcRpTRLRUQlhUJSH

#include "breath/meta/constant.hpp"

namespace breath {
namespace meta {

//      has_sign:
//      =========
//
//!     A \c meta::constant yielding whether a type allows negative
//!     values.
// ---------------------------------------------------------------------------
template< typename T >
class has_sign
    // The natural form here would be "T( -1 ) < 0"; but GCC, and
    // possibly other compilers, would warn when instantiating the
    // template with T being an unsigned type. Of course it also
    // warns if using "!( T( -1 ) >= 0 )"
    // -----------------------------------------------------------------------
    :   public constant< bool, ! ( T( -1 ) > 0 ) >
{
} ;

//      The specialization here is logically unnecessary but silences
//      compiler warnings.
// ---------------------------------------------------------------------------
template<>
class has_sign< bool >
    :   public constant< bool, false >
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
