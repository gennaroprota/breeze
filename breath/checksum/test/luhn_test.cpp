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

#include "breath/checksum/luhn.hpp"
#include "breath/iteration/begin_end.hpp"
#include "breath/testing/testing.hpp"
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
        BREATH_CHECK( breath::luhn_sum( e.text ) == e.luhn_sum ) ;
        BREATH_CHECK( breath::luhn_check_digit( e.text ) == e.digit ) ;

        BREATH_CHECK( breath::has_luhn_sum( e.text + e.digit ) ) ;
    }

    BREATH_CHECK( ! breath::has_luhn_sum( "" ) ) ;
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
        BREATH_CHECK_THROW( std::invalid_argument, breath::luhn_sum( s ) ) ;
        BREATH_CHECK_THROW( std::invalid_argument, breath::has_luhn_sum( s ) ) ;
        BREATH_CHECK_THROW( std::invalid_argument, breath::luhn_check_digit( s ) ) ;
    }
}

}

int
test_luhn()
{
    using namespace breath ;

    return test_runner::instance().run( "Luhn routines",
                                        { check_known_sums,
                                      luhn_routines_throw_on_invalid_chars } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
