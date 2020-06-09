// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/uuid/uuid.hpp"
#include "breath/testing/testing.hpp"
#include "breath/text/to_string.hpp"
#include <iostream>
#include <map>
#include <ostream>
#include <string>

int                 test_uuid() ;

namespace {

void
do_tests()
{
    {
        breath::uuid        nil ;
        BREATH_CHECK( breath::to_string( nil ) ==
                      "00000000-0000-0000-0000-000000000000" ) ;
    }

    {
        breath::uuid const  uu( breath::uuid::rfc_4122,
                                breath::uuid::time_based ) ;

        BREATH_CHECK( uu.variant() == breath::uuid::rfc_4122 ) ;
        BREATH_CHECK( uu.version() == breath::uuid::time_based ) ;

        std::string const   representation = breath::to_string( uu ) ;
        char const          hyphen = '-' ;

        BREATH_CHECK( representation[  8 ] == hyphen &&
                      representation[ 13 ] == hyphen &&
                      representation[ 18 ] == hyphen &&
                      representation[ 23 ] == hyphen    ) ;
    }

    //      Test operator ==() and operator !=().
    // -----------------------------------------------------------------------
    {
        breath::uuid const  nil ;
        BREATH_CHECK( nil == breath::uuid::nil() ) ;

        breath::uuid const  uu( breath::uuid::rfc_4122,
                                breath::uuid::time_based ) ;

        BREATH_CHECK( nil != uu ) ;
    }

    //      Test usability with std::map.
    // -----------------------------------------------------------------------
    {
        std::map< breath::uuid, int, breath::uuid::less >
                            m ;
        m[ breath::uuid::nil() ] = 1 ;
    }
}

}


int
main()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { do_tests } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
