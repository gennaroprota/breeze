// ===========================================================================
//                     Copyright 2018-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief The representation of a non-negative integer, in base b.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_lqF1VhyaeQBA6t5SZLvv9rpFKK1iZVzu
#define BREATH_GUARD_lqF1VhyaeQBA6t5SZLvv9rpFKK1iZVzu

#include <string>

namespace breath {

//!     \pre
//!         n >= 0 && base >= 2 && base <= 36
//!
//!     \return
//!         The representation, in base \c base, of the integer \c n.
// -------------------------------------------------------------------------
template< typename T >
std::string
representation_in_base( T n, T base ) ;

}

#include "brt/representation_in_base.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
