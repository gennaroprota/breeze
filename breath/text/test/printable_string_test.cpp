// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2015-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/testing/testing.hpp"
#include "breath/text/printable_string.hpp"
#include <iostream>
#include <sstream>

int                 test_printable_string() ;

namespace {

void
do_test()
{
    using breath::printable_string ;

    {
        printable_string const
                            p( nullptr ) ;
        std::ostringstream  ss ;
        ss << p ;
        BREATH_CHECK( ! ss.fail() ) ;
        BREATH_CHECK( ss.str() == "(null)" ) ;
    }

    {
        printable_string const
                            p( "\'\"\?\\\a\b\f\n\r\t\v\x1\x2\x3\x1F\x20\x7e\x7F"
                               "\xA0\xFF" ) ;
        std::ostringstream  ss ;
        ss.setf( std::ios_base::left, std::ios_base::adjustfield ) ;
        ss.setf( std::ios_base::showbase ) ;
        ss << p ;
        BREATH_CHECK( ! ss.fail() ) ;
        BREATH_CHECK( ss.str() == "\"'\\\"\\?\\\\\\a\\b\\f\\n\\r\\t\\v\\x01"
                             "\\x02\\x03\\x1f ~\\x7f\\xa0\\xff\"") ;
    }

    {
        printable_string const
                            no_trigraph( "\?\?!" ) ;
        std::ostringstream  ss ;
        ss << no_trigraph ;
        BREATH_CHECK( ! ss.fail() ) ;
        BREATH_CHECK( ss.str() == "\"\\?\\?!\"" ) ;
    }
}

}

int
test_printable_string()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run(
             "printable_string",
             { do_test } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
