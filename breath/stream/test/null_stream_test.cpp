// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/stream/null_stream.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>
#include <sstream>

int                 test_null_stream() ;

namespace {

void
check()
{
    {
        breath::null_stream s ;
        std::stringstream   ss ;
        static_cast< std::ostream & >( ss ).rdbuf( s.rdbuf() ) ;
        ss << "ignored" ;
        BREATH_CHECK( ss.str() == "" ) ;
    }
    {
        breath::null_stream s ;
        s << "ignored" ;
        BREATH_CHECK( s.good() ) ;
    }
    {
        breath::null_stream s ;
        int i = 0 ;
        s >> i ;
        BREATH_CHECK( s.eof() ) ;
        BREATH_CHECK( s.fail() ) ;
        BREATH_CHECK( ! s.bad() ) ;
        BREATH_CHECK( i == 0 ) ;
    }
}

}

int
test_null_stream()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( "null_stream", { check } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
