// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2006-2010 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/diagnostics/assert.hpp"

#include <cstdlib>
#include <iostream>
#include <ostream>

namespace breath {
namespace assert_private {

[[ noreturn ]] void
fire( char const * expression_text,
      char const * file_name, unsigned long line_number ) noexcept
{
    std::cerr << "Assertion failed: "
              << expression_text
              << ", file " << file_name
              << ", line " << line_number
              << std::endl ;

    std::abort() ;
}

}
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
