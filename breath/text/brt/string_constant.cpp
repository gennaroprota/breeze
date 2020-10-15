// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/text/string_constant.hpp"

namespace breath_ns {

char const          latin_small_letters[]   = "abcdefghijklmnopqrstuvwxyz" ;
char const          latin_capital_letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ;

char const          decimal_digits[] = "0123456789" ;
char const          octal_digits[]   = "01234567"   ;

char const          lowercase_hex_digits[] = "0123456789abcdef" ;
char const          uppercase_hex_digits[] = "0123456789ABCDEF" ;

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
