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

#include "breeze/diagnostics/last_api_error.hpp"
#include "breeze/process/current_directory.hpp"
#include "breeze/process/set_current_directory.hpp"
#include "breeze/testing/testing.hpp"
#include <string>

int                 test_get_set_current_directory() ;

namespace {

void
check()
{
    {
        std::string const   cur = breeze::current_directory() ;
        breeze::set_current_directory( cur ) ;
    }
    {
        std::string const   nonexisting = "NonExistingDirectoryName" ;
        BREEZE_CHECK_THROW( breeze::last_api_error,
                            breeze::set_current_directory( nonexisting ) ) ;
    }
}

}

int
test_get_set_current_directory()
{
    return breeze::test_runner::instance().run(
        "Get/set current directory",
        { check }
    ) ;
}




// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
