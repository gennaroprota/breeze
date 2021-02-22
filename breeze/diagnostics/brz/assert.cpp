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

#include "breeze/diagnostics/assert.hpp"

#include <cstdlib>
#include <iostream>
#include <ostream>

namespace breeze_ns {
namespace           {

assert_handler_type *
                    g_assert_handler = &default_assert_handler ;

}

[[ noreturn ]] void
default_assert_handler( char const * expression_text,
                        char const * file_name,
                        long line_number ) noexcept
{
    std::cerr << R"(
The program encountered an internal error. Please, contact the developers or
the customer support, providing the following information:

)" ;

    std::cerr << "Assertion failed: "
              << expression_text
              << ", file " << file_name
              << ", line " << line_number
              << std::endl ;

    std::abort() ;
}

void
set_assert_handler( assert_handler_type * f )
{
    //      Note that we *can* assert here. It's just that the assertion
    //      will use the previously active assert handler.
    // -----------------------------------------------------------------------
    BREEZE_ASSERT( f != nullptr ) ;
    g_assert_handler = f ;
}

namespace assert_private {

[[ noreturn ]] void
fire( char const * expression_text,
      char const * file_name,
      long line_number )
{
    ( *g_assert_handler )( expression_text, file_name, line_number ) ;
    std::abort() ;
}

}

}
