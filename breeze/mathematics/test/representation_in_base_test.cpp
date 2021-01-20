// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2018-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/mathematics/representation_in_base.hpp"
#include "breeze/testing/testing.hpp"
#include <cstdint>
#include <limits>
#include <sstream>

int                 test_representation_in_base() ;

namespace {

void check()
{
    {
        int const           min_base = 2 ;
        int const           max_base = 36 ;

        for ( int b = min_base ; b <= max_base ; ++ b ) {
            BREEZE_CHECK( breeze::representation_in_base(  0, b ) == "0" ) ;
            BREEZE_CHECK( breeze::representation_in_base( -1, b ) == "-1" ) ;
        }
    }

    {
        BREEZE_CHECK( breeze::representation_in_base(   64, 16 ) ==  "40" ) ;
        BREEZE_CHECK( breeze::representation_in_base(  -64, 16 ) == "-40" ) ;
        BREEZE_CHECK( breeze::representation_in_base(  169, 16 ) ==  "a9" ) ;
        BREEZE_CHECK( breeze::representation_in_base( -169, 16 ) == "-a9" ) ;
        BREEZE_CHECK( breeze::representation_in_base( 254, 2 ) == "11111110" ) ;
        BREEZE_CHECK( breeze::representation_in_base( 395, 36 ) == "az" ) ;
    }

    {
        std::intmax_t const m = std::numeric_limits< std::intmax_t >::min() ;
        std::ostringstream  ss ;
        ss << m ;
        BREEZE_CHECK( breeze::representation_in_base( m, 10 ) == ss.str() ) ;
    }
}

void
out_of_range_base_causes_assert()
{
    int                 base = 1 ;
    BREEZE_CHECK_THROWS( breeze::assert_failure,
        breeze::representation_in_base( 1, base ) ) ;
    base = 37 ;
    BREEZE_CHECK_THROWS( breeze::assert_failure,
        breeze::representation_in_base( 1, base )) ;
}

}

int
test_representation_in_base()
{
    return breeze::test_runner::instance().run(
        "representation_in_base()",
        { check,
          out_of_range_base_causes_assert } ) ;
}
