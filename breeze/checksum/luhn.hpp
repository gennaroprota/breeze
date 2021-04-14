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

#ifndef BREEZE_GUARD_tIQHBNytA88Bkj4QJcjMo5Tyy8QmG29Y
#define BREEZE_GUARD_tIQHBNytA88Bkj4QJcjMo5Tyy8QmG29Y

#include "breeze/top_level_namespace.hpp"
#include <string>

namespace breeze_ns {

//      luhn_sum():
//      ===========
//
//!\brief
//!     Calculates the Luhn sum of a string.
//!
//!     \return
//!         The Luhn sum of the given string. This is a number in
//!         <tt>[0, 9]</tt>.
//!
//!     \par Exceptions
//!         A `std::invalid_argument` if any of the characters in `s` is
//!         not a decimal digit (i.e. one of <tt>0123456789</tt>).
// ---------------------------------------------------------------------------
int                 luhn_sum( std::string const & s ) ;

//      has_luhn_sum():
//      ===============
//
//!\brief
//!     Verifies a string.
//!
//!     \return
//!         Whether the given string has a Luhn sum as its last
//!         character.
//!
//!     \par Exceptions
//!         A `std::invalid_argument` if any of the characters in `s` is
//!         not a decimal digit (i.e. one of <tt>0123456789</tt>).
// ---------------------------------------------------------------------------
bool                has_luhn_sum( std::string const & s ) ;

//      luhn_check_digit():
//      ===================
//
//!\brief
//!     Calculates a Luhn checksum digit, as a char.
//!
//!     \return
//!         The Luhn checksum digit for the given string. This is a
//!         `char` in `['0', '9']`.
//!
//!     \par Exceptions
//!         A `std::invalid_argument` if any of the characters in `s` is
//!         not a decimal digit (i.e. one of <tt>0123456789</tt>).
// ---------------------------------------------------------------------------
char                luhn_check_digit( std::string const & s ) ;

}

#endif
