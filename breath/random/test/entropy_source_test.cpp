// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2013 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/random/entropy_source.hpp"
#include "breath/testing/testing.hpp"
#include <algorithm>
#include <numeric>
#include <vector>

int                 test_entropy_source() ;

namespace {

void
do_test()
{
    breath::entropy_source
                        source ;

    {
        auto const          value = source.next() ;
        BREATH_CHECK( source.min() <= value &&
                        value <= source.max() ) ;
    }
    {
        int const           maximum = 15 ;
        auto const          capped_value = source( maximum ) ;
        BREATH_CHECK( source.min() <= capped_value &&
                        capped_value <= maximum ) ;
    }
    {
        int const           minimum = 100 ;
        int const           maximum = 200 ;
        auto const          value = source( minimum, maximum ) ;
        BREATH_CHECK( minimum <= value && value <= maximum ) ;
    }

    BREATH_CHECK( source.release() ) ;

    //      Check that a second release doesn't yield "success".
    // -----------------------------------------------------------------------
    BREATH_CHECK( ! source.release() ) ;
}

template< typename RandomIter >
void
all_elements_do_appear_and_once( RandomIter begin, RandomIter end )
{
    auto const          count = end - begin ;
    for ( int i = 0 ; i < count ; ++ i ) {
        BREATH_CHECK( std::count( begin, end, i ) == 1 ) ;
    }
}

void
entropy_source_is_usable_with_shuffle()
{
    //      Note how we test with more than 256 elements (entropy_source
    //      currently generates numbers from 0 to 255).
    // -----------------------------------------------------------------------
    int const           count = 300 ;
    std::vector< int >  v( count ) ;
    std::iota( v.begin(), v.end(), 0 ) ;
    std::shuffle( v.begin(), v.end(), breath::entropy_source() ) ;

    all_elements_do_appear_and_once( v.cbegin(), v.cend() ) ;
}

}

int
test_entropy_source()
{
    using namespace breath ;

    return test_runner::instance().run(
             "entropy_source",
             { do_test,
               entropy_source_is_usable_with_shuffle } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
