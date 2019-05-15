// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Luhn checksum routines.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_tIQHBNytA88Bkj4QJcjMo5Tyy8QmG29Y
#define BREATH_GUARD_tIQHBNytA88Bkj4QJcjMo5Tyy8QmG29Y

#include <string>

namespace breath {

//      luhn_sum():
//      ===========
//
//      \return
//!         The Luhn sum of the given string. This is a number in
//!         <code>[0, 9]</code>.
//!
//!     \throw
//!         A \c breath::exception if any of the characters in \c s is
//!         not a decimal digit.
// ---------------------------------------------------------------------------
int                 luhn_sum( std::string const & s ) ;

//      has_luhn_sum():
//      ===============
//
//!     \return
//!         Whether the given string has a Luhn sum as its last
//!         character.
//!
//!     \throw
//!         A \c breath::exception if any of the characters in \c s is
//!         not a decimal digit.
// ---------------------------------------------------------------------------
bool                has_luhn_sum( std::string const & s ) ;

//      luhn_check_digit():
//      ===================
//
//      \return
//!         The Luhn checksum digit for the given string. This is a char
//!         in ['0', '9'].
//!
//!     \throw
//!         A \c breath::exception if any of the characters in \c s is
//!         not a decimal digit.
// ---------------------------------------------------------------------------
char                luhn_check_digit( std::string const & s ) ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
