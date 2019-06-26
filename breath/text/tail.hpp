// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#ifndef BREATH_GUARD_48671WeJXu9JNdXpT04IlPYpPx1GCY0K
#define BREATH_GUARD_48671WeJXu9JNdXpT04IlPYpPx1GCY0K

#include <cstddef>
#include <string>

namespace breath {

//!     \return
//!         If <code>count >= s.length()</code>, \c s; otherwise the
//!         string composed of the last \c count characters of \c s.
// ---------------------------------------------------------------------------
std::string         tail( std::string const & s, std::size_t count ) ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
