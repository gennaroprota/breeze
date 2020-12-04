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

#include "breeze/memory/auto_array.hpp"
#include "breeze/testing/testing.hpp"
#include <vector>

int                 test_auto_array() ;

namespace {

breeze::auto_array< int >
f()
{
    return breeze::auto_array< int >( new int[ 3 ]{ 0, 1, 2 } ) ;
}

void
check_move_semantics()
{
    // Check that the move constructor is in effect.
    //
    breeze::auto_array< int > a = f() ;
    for ( int i = 0 ; i < 3 ; ++i ) {
        BREEZE_CHECK( a.get()[ i ] == i ) ;
    }
    // Check also the move assignment operator.
    // NOTE: this is bad code, with a hard-coded constant (3) and
    // hard-coded values (plus, code repetition).
    a = f() ;
    for ( int i = 0 ; i < 3 ; ++i ) {
        BREEZE_CHECK( a.get()[ i ] == i ) ;
    }
}

void
check_non_move_constructors()
{
    breeze::auto_array< std::string >
                        a( new std::string[ 2 ]{ "foo", "bar" } ) ;
    BREEZE_CHECK( a.get()[ 0 ] == "foo" ) ;
    BREEZE_CHECK( a.get()[ 1 ] == "bar" ) ;

    breeze::auto_array< double > deflt ;
    BREEZE_CHECK( deflt.get() == nullptr ) ;

    breeze::auto_array< char > n( nullptr ) ;
    BREEZE_CHECK( n.get() == nullptr ) ;

}

void
check_reset()
{
    // The case reset( nullptr ) is an important one.
    //
    // TODO: should we check if operator delete[]() is called with the
    //       correct pointer value?
    //
    breeze::auto_array< std::vector< int > >
                        a( new std::vector< int >[ 100 ] ) ;
    a.reset( new std::vector< int >[ 5 ]) ;
    a.reset( nullptr ) ;
}

void
can_assign_elements_of_const_auto_array_to_non_const()
{
    {
        int *               p = new int [ 5 ]{ 0, 1, 2, 3, 4 } ;
        breeze::auto_array< int > const
                            a( p ) ;
        a.get()[ 0 ] = 0 ;
    }
}

}

int
test_auto_array()
{
    using namespace breeze ;

    return test_runner::instance().run( "auto_array",
                  { check_move_semantics,
                    check_non_move_constructors,
                    check_reset,
                    can_assign_elements_of_const_auto_array_to_non_const } ) ;
}
