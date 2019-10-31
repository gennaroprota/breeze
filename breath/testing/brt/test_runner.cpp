// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/testing/test_runner.hpp"

namespace breath {

test_runner::test_runner()
    :   m_reporter( nullptr )
{
}

test_runner &
test_runner::instance()
{
    static test_runner  runner ;
    return runner ;
}

void
test_runner::attach_reporter( test_reporter & rep )
{
    m_reporter = &rep ;
}

int
test_runner::run( std::initializer_list< test_descriptor > list )
{
    return run( list.begin(), list.end() ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
