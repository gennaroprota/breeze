// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2016-2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/diagnostics/exception.hpp"
#include "breath/testing/testing.hpp"
#include <cstddef>
#include <cstring>
#include <exception>
#include <iostream>
#include <string>

void
test_throwability()
{
    try {
        throw breath::exception( "test" ) ;
    } catch ( std::exception const & ) {
    }
}

void
test_what_message_handling()
{
    std::string const   default_message = "Breath library exception" ;

    breath::exception const
                        e1 ;
    breath::exception const
                        e2( "" ) ;
    BREATH_CHECK( e1.what() == default_message ) ;
    BREATH_CHECK( e2.what() == default_message ) ;

    std::string const   very_long_string( 5 * 1024, 'A' ) ;
    breath::exception const
                        e3( very_long_string ) ;

    //      This is, of course, coupled with the particular choice made
    //      in the implementation of the class. But that's not a
    //      problem: if the number will be changed in the implementation
    //      then the test will fail, and will thus be updated.
    // -----------------------------------------------------------------------
    BREATH_CHECK( std::strlen( e3.what() ) == 1022 ) ;
}

void
test_copy()
{
    breath::exception   ex( "test" ) ;
    breath::exception   ex2( ex ) ;
    BREATH_CHECK( std::strcmp( ex.what(), ex2.what() ) == 0 ) ;

    breath::exception   ex3 ;
    ex3 = ex ;
    BREATH_CHECK( std::strcmp( ex.what(), ex3.what() ) == 0 ) ;
}

int
main()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { test_throwability,
                                          test_what_message_handling,
                                          test_copy } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
