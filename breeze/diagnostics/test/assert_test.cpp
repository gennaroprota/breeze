// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/diagnostics/assert.hpp"
#include "breeze/testing/testing.hpp"

int                 test_breeze_assert() ;

namespace {

constexpr int
check_constexpr()
{
    BREEZE_ASSERT( true ) ;
    return 1 ;
}

void
do_test()
{
    //      TODO: we'd need tests to verify that types other than bool
    //      or cv-qualified bool don't compile. And that
    //      BREEZE_ASSERT( false ) aborts the program. I'll provide them
    //      when we'll have the necessary infrastructure for such tests.
    // -----------------------------------------------------------------------
    bool                b1 = true ;
    bool const          b2 = true ;
    bool volatile       b3 = true ;
    bool const volatile b4 = true ;

    BREEZE_ASSERT( b1 ) ;
    BREEZE_ASSERT( b2 ) ;
    BREEZE_ASSERT( b3 ) ;
    BREEZE_ASSERT( b4 ) ;

    constexpr int       n = check_constexpr() ;
    static_cast< void >( n ) ;
}

class my_exception
{
} ;

[[ noreturn ]] void
my_assert_handler( char const *, char const *, long )
{
    throw my_exception() ;
}

void
failed_assertion_calls_active_handler()
{
    breeze::set_assert_handler( my_assert_handler ) ;

    BREEZE_CHECK_THROW( my_exception, BREEZE_ASSERT( false ) ) ;
}

}

int
test_breeze_assert()
{
    return breeze::test_runner::instance().run(
        "BREEZE_ASSERT()",
        { do_test,
          failed_assertion_calls_active_handler } ) ;
}
