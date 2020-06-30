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

#include "breath/testing/test_reporter.hpp"

namespace breath_ns {

test_reporter::test_reporter() = default ;

void
test_reporter::on_all_tests_begin( char const * group_description )
{
    return do_on_all_tests_begin( group_description ) ;
}

void
test_reporter::on_all_tests_end()
{
    return do_on_all_tests_end() ;
}

void
test_reporter::on_test_begin( int test_number, char const * name )
{
    return do_on_test_begin( test_number, name ) ;
}

void
test_reporter::on_test_passed( int test_number )
{
    return do_on_test_passed( test_number ) ;
}

void
test_reporter::on_test_failed( int test_number, test_exception const & ex )
{
    return do_on_test_failed( test_number, ex ) ;
}

void
test_reporter::on_unexpected_exception( int test_number )
{
    return do_on_unexpected_exception( test_number ) ;
}

void
test_reporter::on_unexpected_exception( int test_number, std::exception const & ex )
{
    return do_on_unexpected_exception( test_number, ex ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
