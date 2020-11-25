// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2006-2007 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/environment/get_environment_variable.hpp"
#include "breeze/testing/testing.hpp"
#include "breeze/vocabulary/maybe.hpp"
#include <string>

int                 test_get_environment_variable() ;

namespace {

void
do_test()
{
    using namespace breeze ;

    maybe< std::string > const
                        e = get_environment_variable( "BREEZE_ROOT" ) ;

    BREEZE_CHECK( e.is_valid() ) ;
    BREEZE_CHECK( ! e.value().empty() ) ;
}

}

int
test_get_environment_variable()
{
    using namespace breeze ;

    return test_runner::instance().run(
             "get_environment_variable()",
             { do_test } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
