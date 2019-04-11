// =========================================================================
//                This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/conversion/roman.hpp"
#include "breath/environment/find_environment_string.hpp"
#include "breath/testing/testing.hpp"
#include "breath/text/to_string.hpp"

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

void
check()
{
    std::string const   breath_root = breath::find_environment_string(
                                                    "BREATH_ROOT" ).value() ;
    std::ifstream       is( breath_root
                            + "/breath/conversion/test/a006968.txt" ) ;

    // skip the first lines
    int const           lines_to_skip = 14 ;
    for ( int i = 0 ; i < lines_to_skip ; ++ i ) {
        std::string         s ;
        std::getline( is, s ) ;
    }

    int const           max_roman = 3999 ;
    int                 n ;
    do  {
        is >> n ;
        char                equal_sign ;
        is >> equal_sign ;
        std::string         rep ;
        is >> rep ;

        std::string const   s = breath::to_string( breath::roman( n ) ) ;
        BREATH_CHECK( rep == s ) ;
    } while ( n != max_roman ) ;
}

int
main()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { check } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
