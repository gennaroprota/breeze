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

#include "breeze/metric/damerau_levenshtein_distance.hpp"
#include "breeze/testing/testing.hpp"
#include <cstddef>
#include <string>

int                 test_damerau_levenshtein_distance() ;

namespace {

void
single_check( std::string const & first, std::string const & second,
              std::ptrdiff_t distance )
{
    BREEZE_CHECK( breeze::damerau_levenshtein_distance( first, second )
                                                                == distance ) ;
    BREEZE_CHECK( breeze::damerau_levenshtein_distance( second, first )
                                                                == distance ) ;

    //      Any string is distant zero from itself.
    // -----------------------------------------------------------------------
    BREEZE_CHECK( breeze::damerau_levenshtein_distance( first, first ) == 0 ) ;
    BREEZE_CHECK( breeze::damerau_levenshtein_distance( second,
                                                        second ) == 0 ) ;
}

void
check()
{
    single_check( "foo", "", 3 ) ;
    single_check( "hello", "hallo", 1 ) ;
    single_check( "sitting", "kitten", 3 ) ;
    single_check( "spell", "spel", 1 ) ;
    single_check( "suggest", "suggets", 1 ) ;
    single_check( "wikipedia", "encyclopedia", 7 ) ;
    single_check( "abcde", "acbed", 2 ) ;
    single_check( "abcde", "baced", 2 ) ;
    single_check( "abcde", "baecd", 3 ) ;
    single_check( "Smith", "Stitch", 2 ) ;
}

}

int
test_damerau_levenshtein_distance()
{
    return breeze::test_runner::instance().run( "damerau_levenshtein_distance()",
                                        { check } ) ;
}
