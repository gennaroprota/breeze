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

#include "breath/memory/auto_array.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>
#include <vector>

int                 test_auto_array() ;

namespace {

breath::auto_array< int >
f()
{
    return breath::auto_array< int >( new int[ 3 ]{ 0, 1, 2 } ) ;
}

void
check_move_semantics()
{
    // Check that the move constructor is in effect.
    //
    breath::auto_array< int > a = f() ;
    for ( int i = 0 ; i < 3 ; ++i ) {
        BREATH_CHECK( a.get()[ i ] == i ) ;
    }
    // Check also the move assignment operator.
    // NOTE: this is bad code, with a hard-coded constant (3) and
    // hard-coded values (plus, code repetition).
    a = f() ;
    for ( int i = 0 ; i < 3 ; ++i ) {
        BREATH_CHECK( a.get()[ i ] == i ) ;
    }
}

void
check_non_move_constructors()
{
    breath::auto_array< std::string >
                        a( new std::string[ 2 ]{ "foo", "bar" } ) ;
    BREATH_CHECK( a.get()[ 0 ] == "foo" ) ;
    BREATH_CHECK( a.get()[ 1 ] == "bar" ) ;

    breath::auto_array< double > deflt ;
    BREATH_CHECK( deflt.get() == nullptr ) ;

    breath::auto_array< char > n( nullptr ) ;
    BREATH_CHECK( n.get() == nullptr ) ;

}

void
check_reset()
{
    // The case reset( nullptr ) is an important one.
    //
    // TODO: should we check if operator delete[]() is called with the
    //       correct pointer value?
    //
    breath::auto_array< std::vector< int > >
                        a( new std::vector< int >[ 100 ] ) ;
    a.reset( new std::vector< int >[ 5 ]) ;
    a.reset( nullptr ) ;
}

}

int
test_auto_array()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { check_move_semantics,
                                          check_non_move_constructors,
                                          check_reset                 } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
