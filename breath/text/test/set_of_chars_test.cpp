// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/testing/testing.hpp"
#include "breath/text/set_of_chars.hpp"
#include <algorithm>
#include <climits>
#include <iostream>

int                 test_set_of_chars() ;

namespace {

void
do_test()
{
    using breath::set_of_chars ;

    //      Ordinary constructors.
    // -----------------------------------------------------------------------
    {
        set_of_chars const  sc1 ;
        BREATH_CHECK( sc1.is_empty() ) ;

        set_of_chars const  sc2( "a" ) ;
        BREATH_CHECK( sc2.contains( 'a' ) && sc2.count() == 1 ) ;

        std::string         str ;
        str.push_back( '\0' ) ;
        str.push_back( '\0' ) ;
        set_of_chars const  sc3( str ) ;
        BREATH_CHECK( sc3.contains( '\0' ) && sc3.count() == 1 ) ;

        str.push_back( 'x' ) ;
        set_of_chars const sc4( str.cbegin(), str.cend() ) ;
        BREATH_CHECK( sc4.contains( '\0' ) && sc4.contains( 'x')
                                        && sc4.count() == 2 ) ;

        {
            set_of_chars const
                            sc( set_of_chars::except, 'a' ) ;
            for( int n = CHAR_MIN ; n <= CHAR_MAX ; ++ n ) {
                BREATH_CHECK( sc.contains( static_cast< char >( n ) ) ==
                                ( n != 'a' ) ) ;
            }
        }
    }

    //      Copy constructor.
    // -----------------------------------------------------------------------
    {
        set_of_chars const s("abcdefghijklmnopqrstuvwxyz") ;
        set_of_chars const t( s ) ;

        BREATH_CHECK( t == s ) ;
        BREATH_CHECK( t.as_string() == "abcdefghijklmnopqrstuvwxyz" ) ;
    }

    //      contains()
    // -----------------------------------------------------------------------
    {
        set_of_chars const  s( "wxyz") ;
        BREATH_CHECK( s.contains( 'w' ) && s.contains( 'x' ) &&
              s.contains( 'y' ) &&   s.contains( 'z' ) &&
            ! s.contains( 'a' ) && ! s.contains( '\0' ) ) ;
    }

    //      add() / remove()
    // -----------------------------------------------------------------------
    {
        BREATH_CHECK(
            set_of_chars( "abc").add( 'd' ) == set_of_chars( "abcd" ) ) ;
        BREATH_CHECK(
            set_of_chars( "abc").add( "d" ) == set_of_chars( "abcd" ) ) ;
    }
    {
        //      Check that we can add/remove a '\0'.
        // -------------------------------------------------------------------
        BREATH_CHECK( set_of_chars( "" ).is_empty() ) ;
        std::string         s ;
        s.push_back( '\0' ) ;
        set_of_chars        sc ;
        sc.add( s ) ;
        BREATH_CHECK( sc.count() == 1 && sc.contains('\0' ) ) ;
        sc.remove( s ) ;
        BREATH_CHECK( sc.count() == 0 && ! sc.contains( '\0' ) ) ;
    }

    //      complement()
    // -----------------------------------------------------------------------
    {
        std::string s( "ab" ) ;
        set_of_chars        sc( s.cbegin(), s.cend() ) ;
        sc.complement() ;
        for ( int c = CHAR_MIN ; c <= CHAR_MAX ; ++ c ) {
            BREATH_CHECK( sc.contains( static_cast< char >( c ) ) ==
                ( s.find( static_cast< char>( c ) ) == std::string::npos ) ) ;
        }
    }

    //      as_string()
    // -----------------------------------------------------------------------
    {
        std::string const   s =         "cage" ;
        std::string const   s_ordered = "aceg" ;
        set_of_chars const  sc( s ) ;

        BREATH_CHECK( sc.as_string() == s_ordered ) ;
    }

    //      count()
    // -----------------------------------------------------------------------
    {
        set_of_chars        sc ;
        BREATH_CHECK( sc.count() == 0 ) ;
        sc.add( "12345" ) ;
        BREATH_CHECK( sc.count() == 5 ) ;
        sc.add( '6' ) ;
        BREATH_CHECK( sc.count() == 6 ) ;
        sc.remove( "64253" ) ;
        BREATH_CHECK( sc.count() == 1 && sc.contains( '1' ) ) ;

    }

    //      is_empty()
    // -----------------------------------------------------------------------
    {
        set_of_chars        sc ;
        BREATH_CHECK( sc.is_empty() ) ;
        sc.add( "" ) ;
        BREATH_CHECK( sc.is_empty() ) ;
        sc.add( 'x' ) ;
        BREATH_CHECK( ! sc.is_empty() ) ;

    }

    //      Iterators.
    // -----------------------------------------------------------------------
    {
        set_of_chars::iterator
                            default_constructed_iterator ;
        set_of_chars        sc ;
        BREATH_CHECK( sc.begin() == sc.end() ) ;
        BREATH_CHECK( sc.end() == default_constructed_iterator ) ;
        BREATH_CHECK( sc.cbegin() == sc.cend() ) ;
        sc.add( 'a' ) ;
        BREATH_CHECK( *sc.begin() == 'a' ) ;
        BREATH_CHECK( *sc.cbegin() == 'a' ) ;
        BREATH_CHECK( sc.end() == default_constructed_iterator ) ;

        set_of_chars::iterator
                            beg = sc.begin() ;
        BREATH_CHECK( ++ beg == sc.end() ) ;

        sc.add( 'b' ) ;

        set_of_chars::iterator
                            it = std::find( sc.cbegin(), sc.cend(), 'a' ) ;
        BREATH_CHECK( * ( ++ it) == 'b' ) ;

        it = std::find( sc.begin(), sc.end(), 'b' ) ;
        BREATH_CHECK(  it != sc.end() && *it == 'b' ) ;

        BREATH_CHECK( ++ it == sc.end() ) ;

        int const           num = 2 ;
        char const          to_be_found[ num ] = { 'a', 'b' } ;
        it = std::search( sc.cbegin(), sc.cend(),
                          to_be_found, to_be_found + num ) ;
        BREATH_CHECK( it == sc.cbegin() ) ;

        sc.remove( 'b' ) ;
        it = std::find( sc.begin(), sc.end(), 'a' ) ;
        BREATH_CHECK( it == sc.begin() ) ;
        BREATH_CHECK( it != sc.end() && *it == 'a' ) ;
        BREATH_CHECK( std::find( sc.begin(), sc.end(), 'b' ) == sc.end() ) ;

        set_of_chars        sc_min ;
        sc_min.add( static_cast< char >( CHAR_MIN ) ) ;

        BREATH_CHECK( sc_min.begin() != sc_min.end() ) ;
        BREATH_CHECK( *sc_min.begin() == CHAR_MIN ) ;

        sc_min.remove( static_cast< char >( CHAR_MIN ) ) ;
        BREATH_CHECK( sc_min.begin() == sc_min.end() ) ;

        set_of_chars        sc_max ;
        sc_max.add( static_cast< char >( CHAR_MAX ) ) ;

        BREATH_CHECK( sc_max.begin() != sc_max.end() ) ;
        BREATH_CHECK( *sc_max.begin() == CHAR_MAX ) ;

        sc_max.remove( CHAR_MAX ) ;
        BREATH_CHECK( sc_max.begin() == sc_max.end() ) ;
    }
}

}

int
test_set_of_chars()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run(
             "set_of_chars",
             { do_test } ) ;
}


// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
