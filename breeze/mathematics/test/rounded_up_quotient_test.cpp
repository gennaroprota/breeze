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

#include "breeze/mathematics/rounded_up_quotient.hpp"
#include "breeze/testing/testing.hpp"
#include <climits>

int                 test_rounded_up_quotient() ;

namespace {

void
rounded_up_quotient_is_usable_in_constexpr_contexts()
{
    {
        constexpr auto      r = breeze::rounded_up_quotient( 20, 8 ) ;
        static_assert( r == 3, "" ) ;
    }

    {
        constexpr auto      r = breeze::rounded_up_quotient( -20, 8 ) ;
        static_assert( r == -2, "" ) ;
    }
}

//      TODO: can't find a good name for this function; is this a smell?
// ---------------------------------------------------------------------------
void
rounded_up_quotient_handles_several_cases_correctly()
{
    BREEZE_CHECK( breeze::rounded_up_quotient(   0,  5 ) ==  0 ) ;
    BREEZE_CHECK( breeze::rounded_up_quotient(   0, -5 ) ==  0 ) ;
    BREEZE_CHECK( breeze::rounded_up_quotient(   1,  5 ) ==  1 ) ;
    BREEZE_CHECK( breeze::rounded_up_quotient(   1, -5 ) ==  0 ) ;
    BREEZE_CHECK( breeze::rounded_up_quotient(  -1,  5 ) ==  0 ) ;
    BREEZE_CHECK( breeze::rounded_up_quotient(  -1, -5 ) ==  1 ) ;
    BREEZE_CHECK( breeze::rounded_up_quotient(   4,  5 ) ==  1 ) ;
    BREEZE_CHECK( breeze::rounded_up_quotient(   4, -5 ) ==  0 ) ;
    BREEZE_CHECK( breeze::rounded_up_quotient(  -4,  5 ) ==  0 ) ;
    BREEZE_CHECK( breeze::rounded_up_quotient(  -4, -5 ) ==  1 ) ;
    BREEZE_CHECK( breeze::rounded_up_quotient(  14,  5 ) ==  3 ) ;
    BREEZE_CHECK( breeze::rounded_up_quotient(  14, -5 ) == -2 ) ;
    BREEZE_CHECK( breeze::rounded_up_quotient( -14,  5 ) == -2 ) ;
    BREEZE_CHECK( breeze::rounded_up_quotient( -14, -5 ) ==  3 ) ;
    BREEZE_CHECK( breeze::rounded_up_quotient(  15,  5 ) ==  3 ) ;
    BREEZE_CHECK( breeze::rounded_up_quotient(  15, -5 ) == -3 ) ;
    BREEZE_CHECK( breeze::rounded_up_quotient( -15,  5 ) == -3 ) ;
    BREEZE_CHECK( breeze::rounded_up_quotient( -15, -5 ) ==  3 ) ;
    BREEZE_CHECK( breeze::rounded_up_quotient( -1, INT_MIN ) == 0 ) ;
}

void
rounded_up_quotient_doesnt_warn_with_unsigned()
{
    unsigned int const  a = 255 ;
    unsigned int const  b = 16 ;

    BREEZE_CHECK( breeze::rounded_up_quotient( a, b ) == 16 ) ;
}

void
rounded_up_quotient_arguments_can_be_cv_qualified()
{
    int const volatile  a = 20 ;
    int const volatile  b =  8 ;

    BREEZE_CHECK( breeze::rounded_up_quotient( a, b ) == 3 ) ;
}

}

int
test_rounded_up_quotient()
{
    return breeze::test_runner::instance().run(
        "rounded_up_quotient()",
        { rounded_up_quotient_is_usable_in_constexpr_contexts,
          rounded_up_quotient_handles_several_cases_correctly,
          rounded_up_quotient_doesnt_warn_with_unsigned,
          rounded_up_quotient_arguments_can_be_cv_qualified } ) ;
}
