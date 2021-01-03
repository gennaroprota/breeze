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

#include "breeze/mathematics/ceiling_of_quotient.hpp"
#include "breeze/testing/testing.hpp"
#include <climits>

int                 test_ceiling_of_quotient() ;

namespace {

void
ceiling_of_quotient_is_usable_in_constexpr_contexts()
{
    {
        constexpr auto      r = breeze::ceiling_of_quotient( 20, 8 ) ;
        static_assert( r == 3, "" ) ;
    }

    {
        constexpr auto      r = breeze::ceiling_of_quotient( -20, 8 ) ;
        static_assert( r == -2, "" ) ;
    }
}

//      TODO: can't find a good name for this function; is this a smell?
// ---------------------------------------------------------------------------
void
ceiling_of_quotient_handles_several_cases_correctly()
{
    BREEZE_CHECK( breeze::ceiling_of_quotient(   0,  5 ) ==  0 ) ;
    BREEZE_CHECK( breeze::ceiling_of_quotient(   0, -5 ) ==  0 ) ;
    BREEZE_CHECK( breeze::ceiling_of_quotient(   1,  5 ) ==  1 ) ;
    BREEZE_CHECK( breeze::ceiling_of_quotient(   1, -5 ) ==  0 ) ;
    BREEZE_CHECK( breeze::ceiling_of_quotient(  -1,  5 ) ==  0 ) ;
    BREEZE_CHECK( breeze::ceiling_of_quotient(  -1, -5 ) ==  1 ) ;
    BREEZE_CHECK( breeze::ceiling_of_quotient(   4,  5 ) ==  1 ) ;
    BREEZE_CHECK( breeze::ceiling_of_quotient(   4, -5 ) ==  0 ) ;
    BREEZE_CHECK( breeze::ceiling_of_quotient(  -4,  5 ) ==  0 ) ;
    BREEZE_CHECK( breeze::ceiling_of_quotient(  -4, -5 ) ==  1 ) ;
    BREEZE_CHECK( breeze::ceiling_of_quotient(  14,  5 ) ==  3 ) ;
    BREEZE_CHECK( breeze::ceiling_of_quotient(  14, -5 ) == -2 ) ;
    BREEZE_CHECK( breeze::ceiling_of_quotient( -14,  5 ) == -2 ) ;
    BREEZE_CHECK( breeze::ceiling_of_quotient( -14, -5 ) ==  3 ) ;
    BREEZE_CHECK( breeze::ceiling_of_quotient(  15,  5 ) ==  3 ) ;
    BREEZE_CHECK( breeze::ceiling_of_quotient(  15, -5 ) == -3 ) ;
    BREEZE_CHECK( breeze::ceiling_of_quotient( -15,  5 ) == -3 ) ;
    BREEZE_CHECK( breeze::ceiling_of_quotient( -15, -5 ) ==  3 ) ;
    BREEZE_CHECK( breeze::ceiling_of_quotient( -1, INT_MIN ) == 1 ) ;
}

void
ceiling_of_quotient_doesnt_warn_with_unsigned()
{
    unsigned int const  a = 255 ;
    unsigned int const  b = 16 ;

    BREEZE_CHECK( breeze::ceiling_of_quotient( a, b ) == 16 ) ;
}

void
ceiling_of_quotient_arguments_can_be_cv_qualified()
{
    int const volatile  a = 20 ;
    int const volatile  b =  8 ;

    BREEZE_CHECK( breeze::ceiling_of_quotient( a, b ) == 3 ) ;
}

void
null_divisor_causes_assert()
{
    BREEZE_CHECK_THROW( breeze::assert_failure,
        breeze::ceiling_of_quotient( 1, 0 ) ) ;
}

void
overflow_in_division_causes_assert()
{
    BREEZE_CHECK_THROW( breeze::assert_failure,
        breeze::ceiling_of_quotient( INT_MIN, -1 ) ) ;
}

}

int
test_ceiling_of_quotient()
{
    return breeze::test_runner::instance().run(
        "ceiling_of_quotient()",
        { ceiling_of_quotient_is_usable_in_constexpr_contexts,
          ceiling_of_quotient_handles_several_cases_correctly,
          ceiling_of_quotient_doesnt_warn_with_unsigned,
          ceiling_of_quotient_arguments_can_be_cv_qualified,

          null_divisor_causes_assert,
          overflow_in_division_causes_assert } ) ;
}
