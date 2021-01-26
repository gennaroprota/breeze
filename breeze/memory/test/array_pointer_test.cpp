// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/memory/array_pointer.hpp"
#include "breeze/testing/testing.hpp"
#include <vector>

int                 test_array_pointer() ;

namespace {

breeze::array_pointer< int >
f()
{
    return breeze::array_pointer< int >( new int[ 3 ]{ 0, 1, 2 } ) ;
}

void
check_move_semantics()
{
    // Check that the move constructor is in effect.
    //
    breeze::array_pointer< int > a = f() ;
    for ( int i = 0 ; i < 3 ; ++i ) {
        BREEZE_CHECK( a.raw_pointer()[ i ] == i ) ;
    }
    // Check also the move assignment operator.
    // NOTE: this is bad code, with a hard-coded constant (3) and
    // hard-coded values (plus, code repetition).
    a = f() ;
    for ( int i = 0 ; i < 3 ; ++i ) {
        BREEZE_CHECK( a.raw_pointer()[ i ] == i ) ;
    }
}

void
check_non_move_constructors()
{
    breeze::array_pointer< std::string >
                        a( new std::string[ 2 ]{ "foo", "bar" } ) ;
    BREEZE_CHECK( a.raw_pointer()[ 0 ] == "foo" ) ;
    BREEZE_CHECK( a.raw_pointer()[ 1 ] == "bar" ) ;

    breeze::array_pointer< double > deflt ;
    BREEZE_CHECK( deflt.raw_pointer() == nullptr ) ;

    breeze::array_pointer< char > n( nullptr ) ;
    BREEZE_CHECK( n.raw_pointer() == nullptr ) ;

}

void
check_reset()
{
    // The case reset( nullptr ) is an important one.
    //
    // TODO: should we check if operator delete[]() is called with the
    //       correct pointer value?
    //
    breeze::array_pointer< std::vector< int > >
                        a( new std::vector< int >[ 100 ] ) ;
    a.reset( new std::vector< int >[ 5 ]) ;
    a.reset( nullptr ) ;
}

void
can_assign_elements_through_const_array_pointer_to_non_const()
{
    {
        int *               p = new int [ 5 ]{ 0, 1, 2, 3, 4 } ;
        breeze::array_pointer< int > const
                            a( p ) ;
        a.raw_pointer()[ 0 ] = 0 ;
    }
}

}

int
test_array_pointer()
{
    return breeze::test_runner::instance().run(
        "array_pointer",
        { check_move_semantics,
          check_non_move_constructors,
          check_reset,
          can_assign_elements_through_const_array_pointer_to_non_const } ) ;
}
