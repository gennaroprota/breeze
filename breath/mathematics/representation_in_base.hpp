// ===========================================================================
//                     Copyright 2018-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief The representation of an integer in a given base.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_lqF1VhyaeQBA6t5SZLvv9rpFKK1iZVzu
#define BREATH_GUARD_lqF1VhyaeQBA6t5SZLvv9rpFKK1iZVzu

#include <string>

namespace breath {

//!     \pre
//!         base >= 2 && base <= 36
//!
//!     \return
//!         The representation, in base \c base, of the integer \c n. A
//!         negative value is represented as the character '-' (minus)
//!         immediately followed by the representation of its absolute
//!         value (in the mathematical sense: \c the minimum value of \c
//!         T is handled correctly, even on a two's complement
//!         implementation).
// ---------------------------------------------------------------------------
template< typename T >
std::string
representation_in_base( T n, int base ) ;

}

#include "brt/representation_in_base.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
