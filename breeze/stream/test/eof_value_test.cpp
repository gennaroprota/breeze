// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/stream/eof_value.hpp"
#include "breeze/testing/testing.hpp"
#include <sstream>

int                 test_eof_value() ;

namespace {

void
check()
{
    {
        std::stringstream   ss ;
        BREEZE_CHECK( breeze::is_eof_value( ss.peek(), ss ) ) ;
        BREEZE_CHECK( breeze::is_eof_value( breeze::eof_value( ss ), ss ) ) ;

        ss.clear() ;
        ss << "foo" ;
        BREEZE_CHECK( ! breeze::is_eof_value( ss.peek(), ss ) ) ;
    }
}

}

int
test_eof_value()
{
    return breeze::test_runner::instance().run(
        "eof_value()/is_eof_value()",
        { check } ) ;
}
