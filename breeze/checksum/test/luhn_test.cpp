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

#include "breeze/checksum/luhn.hpp"
#include "breeze/iteration/begin_end.hpp"
#include "breeze/testing/testing.hpp"
#include <stdexcept>
#include <string>

int                 test_luhn() ;

namespace {

void
check_known_sums()
{
    struct
    {
        std::string text ;
        int luhn_sum ;
        char digit ;

    } const             known[] =
    {
        { "",           0, '0' },
        { "1",          1, '8' },
        { "12",         4, '5' },
        { "123",        8, '0' },
        { "1234",       4, '4' },
        { "12345",      1, '5' },
        { "123456",     1, '6' },
        { "1234567",    1, '4' },
        { "12345678",   4, '2' },
        { "123456789",  7, '7' },
        { "478294513",  8, '5' },
        { "8510293847392103485729301287451276780259", 3, '3' }
      } ;

    for ( auto const & e : known ) {
        BREEZE_CHECK( breeze::luhn_sum( e.text ) == e.luhn_sum ) ;
        BREEZE_CHECK( breeze::luhn_check_digit( e.text ) == e.digit ) ;

        BREEZE_CHECK( breeze::has_luhn_sum( e.text + e.digit ) ) ;
    }

    BREEZE_CHECK( ! breeze::has_luhn_sum( "" ) ) ;
}

void
luhn_routines_throw_on_invalid_chars()
{
    std::string const   with_nul( 1, '\0' ) ;
    std::string const   invalid_strings[] =
    {
        "abc",
        with_nul
    } ;

    for ( auto const & s : invalid_strings ) {
        BREEZE_CHECK_THROW( std::invalid_argument, breeze::luhn_sum( s ) ) ;
        BREEZE_CHECK_THROW( std::invalid_argument, breeze::has_luhn_sum( s ) ) ;
        BREEZE_CHECK_THROW( std::invalid_argument, breeze::luhn_check_digit( s ) ) ;
    }
}

}

int
test_luhn()
{
    using namespace breeze ;

    return test_runner::instance().run( "Luhn routines",
                                        { check_known_sums,
                                      luhn_routines_throw_on_invalid_chars } ) ;
}
