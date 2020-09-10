// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/counting/counter.hpp"
#include "breath/testing/testing.hpp"
#include <limits>

int                 test_counter() ;

namespace {

template< typename T >
void
do_check()
{
    using breath::counter ;

    {
        counter< T >        c ;
        BREATH_CHECK( c.value() == 0 ) ;

        ++ c ;
        BREATH_CHECK( c.value() == 1 ) ;

        -- c ;
        BREATH_CHECK( c.value() == 0 ) ;

        c = counter< T >( 15 ) ;
        BREATH_CHECK( c.value() == 15 ) ;
    }

    {
        T const             max = std::numeric_limits< T >::max() ;
        counter< T >        c( max ) ;
        -- c ;
        BREATH_CHECK( c.value() == ( max - 1 ) ) ;
        ++ c ;
        BREATH_CHECK( c.value() == max ) ;
    }

    {
        counter< T >        c( 100 ) ;

        auto const          old = c ++ ;
        BREATH_CHECK( old.value() == 100 ) ;
        BREATH_CHECK( c.value() == 101 ) ;
    }

    {
        counter< T >        c( 100 ) ;

        auto const          old = c -- ;
        BREATH_CHECK( old.value() == 100 ) ;
        BREATH_CHECK( c.value() == 99 ) ;
    }

    {
        counter< T > const  c1( 1 ) ;
        counter< T > const  c2( 2 ) ;

        BREATH_CHECK( c1 < c2 ) ;
        BREATH_CHECK( c2 > c1 ) ;

        counter< T > const  copy( c1 ) ;
        BREATH_CHECK( copy == c1 ) ;
        BREATH_CHECK( copy <  c2 ) ;
        BREATH_CHECK( c2 > copy ) ;
    }
}

}

int
test_counter()
{
    using namespace breath ;

    return test_runner::instance().run(
        "counter",
        { do_check< signed char >,
          do_check< unsigned char >,
          do_check< int >,
          do_check< unsigned int > } ) ;
}



// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
