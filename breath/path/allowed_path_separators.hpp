// =========================================================================
//                    Copyright 2015-2017 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief Returns the allowed path separators in the running
//!            system.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_bvA1h6sHG51DDAzrkOaJBHIxlZBpgVnA
#define BREATH_GUARD_bvA1h6sHG51DDAzrkOaJBHIxlZBpgVnA

namespace breath {

//!     Note that the separators are returned with the "preferred" one
//!     first.
//!
//!     Visual Studio 2015 and 2017 fail to link if I declare this
//!     function as constexpr, so I avoid that for now.
// -------------------------------------------------------------------------
char const *        allowed_path_separators() noexcept ; //gps constexpr?

}
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
