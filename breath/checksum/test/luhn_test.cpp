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
#include "breath/testing/check.hpp"
#include "breath/testing/console_reporter.hpp"
#include "breath/testing/test_runner.hpp"
#include <iostream>
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

    for ( auto it = breath::cbegin( known ) ; it != breath::cend( known ) ; ++ it ) {
        BREATH_CHECK( breath::luhn_sum( it->text ) == it->luhn_sum ) ;
        BREATH_CHECK( breath::luhn_check_digit( it->text ) == it->digit ) ;
    }
}

}

int
test_luhn()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( "Luhn routines",
                                        { check_known_sums } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
