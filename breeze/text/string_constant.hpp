// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Some handy string constants, to ward off typos.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_wplhDlv93m4IYa4dq5axot40P0JWC7Ar
#define BREEZE_GUARD_wplhDlv93m4IYa4dq5axot40P0JWC7Ar

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//!\brief
//!     The string <tt>"abcdefghijklmnopqrstuvwxyz"</tt>.
//!
//!     \note
//!         This is not a \c std::string, to avoid any initialization
//!         order issues.
// ---------------------------------------------------------------------------
extern char const   latin_small_letters[] ;

//!\brief
//!     The string <tt>"ABCDEFGHIJKLMNOPQRSTUVWXYZ"</tt>.
//!
//!     \copydetails latin_small_letters
// ---------------------------------------------------------------------------
extern char const   latin_capital_letters[] ;

//!\brief
//!     The string <tt>"0123456789"</tt>.
//!
//!     \copydetails latin_small_letters
// ---------------------------------------------------------------------------
extern char const   decimal_digits[] ;

//!\brief
//!     The string <tt>"01234567"</tt>.
//!
//!     \copydetails latin_small_letters
// ---------------------------------------------------------------------------
extern char const   octal_digits[] ;

//!\brief
//!     The string <tt>"0123456789abcdef"</tt>.
//!
//!     \copydetails latin_small_letters
// ---------------------------------------------------------------------------
extern char const   lowercase_hex_digits[] ;

//!\brief
//!     The string <tt>"0123456789ABCDEF"</tt>.
//!
//!     \copydetails latin_small_letters
// ---------------------------------------------------------------------------
extern char const   uppercase_hex_digits[] ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
