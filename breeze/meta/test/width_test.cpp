// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2021 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/meta/width.hpp"
#include "breeze/testing/testing.hpp"
#include <climits>

int                 test_width() ;

using breeze::meta::width ;

namespace {

void
width_of_unsigned_char_equals_char_bit()
{
    static_assert( width< unsigned char >::value == CHAR_BIT, "" ) ;
}


void
width_of_unsigned_equals_width_of_corresponding_signed()
{
    static_assert( width< unsigned >::value == width< int >::value, "" ) ;
    static_assert( width< unsigned char >::value ==
                   width< signed char >::value, "" ) ;
}

//      This test is worth having, because meta::constant isn't usable
//      with a volatile-qualified type.
// ---------------------------------------------------------------------------
void
width_is_usable_with_cv_qualified_types()
{
    typedef int         T1 ;
    typedef int const   T2 ;
    typedef int volatile
                        T3 ;
    typedef int const volatile
                        T4 ;

    static_assert( width< T1 >::value == width< T2 >::value, "" ) ;
    static_assert( width< T2 >::value == width< T3 >::value, "" ) ;
    static_assert( width< T3 >::value == width< T4 >::value, "" ) ;
}

}

int
test_width()
{
    return breeze::test_runner::instance().run(
        "width",
        { width_of_unsigned_char_equals_char_bit,
          width_of_unsigned_equals_width_of_corresponding_signed,
          width_is_usable_with_cv_qualified_types } ) ;
}
