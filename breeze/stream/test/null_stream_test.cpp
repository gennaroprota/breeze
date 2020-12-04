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

#include "breeze/stream/null_stream.hpp"
#include "breeze/testing/testing.hpp"
#include <sstream>

int                 test_null_stream() ;

namespace {

void
check()
{
    {
        breeze::null_stream s ;
        std::stringstream   ss ;
        static_cast< std::ostream & >( ss ).rdbuf( s.rdbuf() ) ;
        ss << "ignored" ;
        BREEZE_CHECK( ss.str() == "" ) ;
    }
    {
        breeze::null_stream s ;
        s << "ignored" ;
        BREEZE_CHECK( s.good() ) ;
    }
    {
        breeze::null_stream s ;
        int i = 0 ;
        s >> i ;
        BREEZE_CHECK( s.eof() ) ;
        BREEZE_CHECK( s.fail() ) ;
        BREEZE_CHECK( ! s.bad() ) ;
        BREEZE_CHECK( i == 0 ) ;
    }
}

}

int
test_null_stream()
{
    using namespace breeze ;

    return test_runner::instance().run( "null_stream", { check } ) ;
}
