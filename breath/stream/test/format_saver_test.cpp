// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/stream/format_saver.hpp"
#include "breath/testing/testing.hpp"
#include <iomanip>
#include <iostream>
#include <ostream>
#include <sstream>

void
check()
{
    using breath::format_saver ;
    std::stringstream   str ;
    {
        format_saver        saver( str ) ;
        str.setf( std::ios::hex, std::ios::basefield ) ;
        str.fill( '0' ) ;
        str << std::setw( 2 ) << 15 ;
        BREATH_CHECK( str.str() == "0f" ) ;
    }
    BREATH_CHECK( (str.flags() & std::ios::hex) == 0 ) ;
    BREATH_CHECK( str.fill() == ' ' ) ;
    BREATH_CHECK( str.width() == 0 ) ;
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
