// ===========================================================================
//                        Copyright 2013 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Displays an expression to \c std::cout.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_v4ifHvyokFutGDGkksKs5kPv6rpDcUGv
#define BREEZE_GUARD_v4ifHvyokFutGDGkksKs5kPv6rpDcUGv

#include "breeze/preprocessing/stringize_after_expansion.hpp"
#include <cstring>
#include <iostream>
#include <ostream> // not necessary in C++11

//      BREEZE_DUMP_EXPRESSION():
//      =========================
//
//!     \hideinitializer
//!
//!     A simple macro for quickly dumping a variable or, generally, an
//!     expression to \c std::cout.
//!
//!     It was born as "DUMP_VARIABLE" but then I immediately found a
//!     usage where I wanted to display something like <code>i + j
//!     </code>, so I renamed it to "DUMP_EXPRESSION".
//!
//!     It's intended that you use this just for quick and dirty checks,
//!     and that you *remove* it after that.
//!
//!     The expression is shown in the form <code><expression> = value
//!     </code>. If \c expression contains macro invocations, the macros
//!     are expanded, but the unexpanded form is displayed, too. In any
//!     case, the output ends with \c std::endl.
//!
//!     \note
//!         The <code>#include</code>'s are not part of the interface.
// ---------------------------------------------------------------------------
#define BREEZE_DUMP_EXPRESSION( expression )                                  \
        do {                                                                  \
            char const              expanded[] =                              \
                             BREEZE_STRINGIZE_AFTER_EXPANSION( expression ) ; \
            char const              unexpanded[] = # expression ;             \
            std::ostream &          os = std::cout ;                          \
            os << expanded << " = " << ( expression ) ;                       \
            if ( std::strcmp( expanded, unexpanded ) != 0 ) {                 \
                os << " [from: " << unexpanded << ']' ;                       \
            }                                                                 \
            os << std::endl ;                                                 \
        } while ( false )                                                  /**/

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
