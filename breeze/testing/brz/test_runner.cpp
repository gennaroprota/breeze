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

#include "breeze/testing/test_runner.hpp"
#include "breeze/testing/stream_reporter.hpp"
#include <iostream>

namespace breeze_ns {
namespace           {

test_reporter &
get_default_test_reporter()
{
    static stream_reporter
                        r( std::cout ) ;
    return r ;
}

}

test_runner::test_runner()
    :   m_reporter( &get_default_test_reporter() )
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
test_runner::run( char const * group_description,
                  std::initializer_list< test_descriptor > list )
{
    return run( group_description, list.begin(), list.end() ) ;
}

}
