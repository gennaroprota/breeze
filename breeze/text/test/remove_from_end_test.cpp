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

#include "breeze/text/remove_from_end.hpp"
#include "breeze/testing/testing.hpp"

int                 test_remove_from_end() ;

namespace {

void do_tests()
{
    BREEZE_CHECK( breeze::remove_from_end( "hello world", "world" ) ==
                                                                    "hello " ) ;
    BREEZE_CHECK( breeze::remove_from_end( "",      "" ) == "" ) ;
    BREEZE_CHECK( breeze::remove_from_end( "dummy", "" ) == "dummy" ) ;
    BREEZE_CHECK( breeze::remove_from_end( "nel mezzo del", "cammin" ) ==
                                                              "nel mezzo del") ;
    BREEZE_CHECK( breeze::remove_from_end( "foo", "foo") == "" ) ;
    BREEZE_CHECK( breeze::remove_from_end( "foo", "xfoo") == "foo" ) ;

    //      Ensure everything works if the two arguments are the same
    //      string.
    // -----------------------------------------------------------------------
    std::string const   test( "test" ) ;
    BREEZE_CHECK( breeze::remove_from_end( test, test ) == "" ) ;
}

void
cannot_remove_any_char_from_an_empty_string()
{
    BREEZE_CHECK( breeze::remove_from_end( "", 'x'  ) == "" ) ;
    BREEZE_CHECK( breeze::remove_from_end( "", '\0' ) == "" ) ;
}

void can_only_remove_the_last_char_from_a_non_empty_string()
{
    BREEZE_CHECK( breeze::remove_from_end( "foo", 'o'  ) == "fo"  ) ;
    BREEZE_CHECK( breeze::remove_from_end( "foo", 'O'  ) == "foo" ) ;
    BREEZE_CHECK( breeze::remove_from_end( "foo", '\0' ) == "foo" ) ;
}

}

int
test_remove_from_end()
{
    return breeze::test_runner::instance().run(
        "remove_from_end()",
        { do_tests,
          cannot_remove_any_char_from_an_empty_string,
          can_only_remove_the_last_char_from_a_non_empty_string } ) ;
}
