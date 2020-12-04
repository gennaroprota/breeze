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

#include "breeze/metric/levenshtein_distance.hpp"
#include "breeze/testing/testing.hpp"
#include <cstddef>
#include <string>

int                 test_levenshtein_distance() ;

namespace {

void
single_check( std::string const & first, std::string const & second,
              std::ptrdiff_t distance )
{
    using breeze::levenshtein_distance ;

    BREEZE_CHECK( levenshtein_distance( first, second ) == distance ) ;
    BREEZE_CHECK( levenshtein_distance( second, first ) == distance ) ;

    //      Any string is distant zero from itself.
    // -----------------------------------------------------------------------
    BREEZE_CHECK( levenshtein_distance( first, first ) == 0 ) ;
    BREEZE_CHECK( levenshtein_distance( second, second ) == 0 ) ;

    //      The distance shall remain the same if both strings are
    //      reversed.
    // -----------------------------------------------------------------------
    std::string const   reversed_first( first.crbegin(), first.crend() ) ;
    std::string const   reversed_second( second.crbegin(), second.crend() ) ;

    BREEZE_CHECK( levenshtein_distance( reversed_first, reversed_second ) ==
                                                                   distance ) ;
    BREEZE_CHECK( levenshtein_distance( reversed_second, reversed_first ) ==
                                                                   distance ) ;
}

void
check()
{
    single_check( "foo", "", 3 ) ;
    single_check( "hello", "hallo", 1 ) ;
    single_check( "sitting", "kitten", 3 ) ;
    single_check( "spell", "spel", 1 ) ;
    single_check( "spell", "aspell", 1 ) ;
    single_check( "suggest", "suggets", 2 ) ;
    single_check( "wikipedia", "encyclopedia", 7 ) ;
}

}

int
test_levenshtein_distance()
{
    return breeze::test_runner::instance().run( "levenshtein_distance()",
                                        { check } ) ;
}
