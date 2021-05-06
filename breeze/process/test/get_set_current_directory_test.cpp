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
#include "breeze/process/get_current_directory.hpp"
#include "breeze/process/set_current_directory.hpp"
#include "breeze/testing/testing.hpp"
#include <string>

int                 test_get_set_current_directory() ;

namespace {

void
can_set_the_directory_which_is_already_current()
{
    std::string const   cur = breeze::get_current_directory() ;
    breeze::set_current_directory( cur ) ;

    BREEZE_CHECK( breeze::get_current_directory() == cur ) ;
}

void
attempting_to_set_a_non_existing_directory_throws_and_doesnt_change_dir()
{
    std::string const   cur = breeze::get_current_directory() ;

    std::string const   nonexisting = "NonExistingDirectoryName" ;
    BREEZE_CHECK_THROWS( breeze::last_api_error,
                         breeze::set_current_directory( nonexisting ) ) ;
    BREEZE_CHECK( breeze::get_current_directory() == cur ) ;
}

}

int
test_get_set_current_directory()
{
    return breeze::test_runner::instance().run(
        "Get/set current directory",
        { can_set_the_directory_which_is_already_current,
   attempting_to_set_a_non_existing_directory_throws_and_doesnt_change_dir } ) ;
}
