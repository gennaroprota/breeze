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

#include "breeze/uuid/uuid.hpp"
#include "breeze/testing/testing.hpp"
#include "breeze/text/to_string.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <string>

int                 test_uuid() ;

namespace {

void
do_tests()
{
    {
        breeze::uuid const  nil ;
        BREEZE_CHECK( breeze::to_string( nil ) ==
                      "00000000-0000-0000-0000-000000000000" ) ;
    }

    {
        breeze::uuid const  uu( breeze::uuid::rfc_4122,
                                breeze::uuid::time_based ) ;

        BREEZE_CHECK( uu.variant() == breeze::uuid::rfc_4122 ) ;
        BREEZE_CHECK( uu.version() == breeze::uuid::time_based ) ;

        std::string const   representation = breeze::to_string( uu ) ;
        char const          hyphen = '-' ;

        BREEZE_CHECK( representation[  8 ] == hyphen &&
                      representation[ 13 ] == hyphen &&
                      representation[ 18 ] == hyphen &&
                      representation[ 23 ] == hyphen    ) ;
    }

    //      Test operator ==() and operator !=().
    // -----------------------------------------------------------------------
    {
        breeze::uuid const  nil ;
        BREEZE_CHECK( nil == breeze::uuid::nil() ) ;

        breeze::uuid const  uu( breeze::uuid::rfc_4122,
                                breeze::uuid::time_based ) ;

        BREEZE_CHECK( uu != nil ) ;
    }

    //      Test usability with std::map.
    // -----------------------------------------------------------------------
    {
        std::map< breeze::uuid, int, breeze::uuid::less >
                            m ;
        m[ breeze::uuid::nil() ] = 1 ;
    }
}

void
uuids_are_distinct()
{
    int const           count = 1000 ;
    std::array< breeze::uuid, count >
                        uuids ;
    for ( int i = 0 ; i < count ; ++ i ) {
        uuids[ i ] = breeze::uuid( breeze::uuid::rfc_4122,
                                   breeze::uuid::time_based ) ;
    }

    std::sort( uuids.begin(), uuids.end(), breeze::uuid::less() ) ;

    //      Outputting directly from here is all but elegant... (TODO?)
    // -----------------------------------------------------------------------
    std::array< breeze::uuid, count >::const_iterator const
                        it = std::adjacent_find( uuids.cbegin(), uuids.cend() ) ;
    if ( it != uuids.cend() ) {
        std::cerr << "    Duplicated uuid's: " << std::endl ;
        std::cerr << "    " << *it             << std::endl ;
        std::cerr << "    " << *( it + 1 )     << std::endl ;
    }

    BREEZE_CHECK( it == uuids.cend() ) ;
}

}


int
test_uuid()
{
    return breeze::test_runner::instance().run(
        "uuid",
        { do_tests,
          uuids_are_distinct } ) ;
}
