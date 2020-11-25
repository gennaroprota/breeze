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

#include "breeze/testing/testing.hpp"
#include "breeze/text/set_of_chars.hpp"
#include <algorithm>
#include <climits>
#include <iterator>
#include <sstream>

int                 test_set_of_chars() ;

namespace {

void
do_test()
{
    using breeze::set_of_chars ;

    //      Ordinary constructors.
    // -----------------------------------------------------------------------
    {
        set_of_chars const  sc1 ;
        BREEZE_CHECK( sc1.is_empty() ) ;

        set_of_chars const  sc2( "a" ) ;
        BREEZE_CHECK( sc2.contains( 'a' ) && sc2.count() == 1 ) ;

        std::string         str ;
        str.push_back( '\0' ) ;
        str.push_back( '\0' ) ;
        set_of_chars const  sc3( str ) ;
        BREEZE_CHECK( sc3.contains( '\0' ) && sc3.count() == 1 ) ;

        str.push_back( 'x' ) ;
        set_of_chars const sc4( str.cbegin(), str.cend() ) ;
        BREEZE_CHECK( sc4.contains( '\0' ) && sc4.contains( 'x')
                                        && sc4.count() == 2 ) ;

        {
            set_of_chars const
                            sc( set_of_chars::except, 'a' ) ;
            for( int n = CHAR_MIN ; n <= CHAR_MAX ; ++ n ) {
                BREEZE_CHECK( sc.contains( static_cast< char >( n ) ) ==
                                ( n != 'a' ) ) ;
            }
        }
    }

    //      Copy constructor.
    // -----------------------------------------------------------------------
    {
        set_of_chars const s( "abcdefghijklmnopqrstuvwxyz" ) ;
        set_of_chars const t( s ) ;

        BREEZE_CHECK( t == s ) ;
        BREEZE_CHECK( t.as_string() == "abcdefghijklmnopqrstuvwxyz" ) ;
    }

    //      contains()
    // -----------------------------------------------------------------------
    {
        set_of_chars const  s( "wxyz") ;
        BREEZE_CHECK( s.contains( 'w' ) && s.contains( 'x' ) &&
              s.contains( 'y' ) &&   s.contains( 'z' ) &&
            ! s.contains( 'a' ) && ! s.contains( '\0' ) ) ;
    }

    //      add() / remove()
    // -----------------------------------------------------------------------
    {
        BREEZE_CHECK(
            set_of_chars( "abc").add( 'd' ) == set_of_chars( "abcd" ) ) ;
        BREEZE_CHECK(
            set_of_chars( "abc").add( "d" ) == set_of_chars( "abcd" ) ) ;
    }
    {
        //      Check that we can add/remove a '\0'.
        // -------------------------------------------------------------------
        BREEZE_CHECK( set_of_chars( "" ).is_empty() ) ;
        std::string         s ;
        s.push_back( '\0' ) ;
        set_of_chars        sc ;
        sc.add( s ) ;
        BREEZE_CHECK( sc.count() == 1 && sc.contains('\0' ) ) ;
        sc.remove( s ) ;
        BREEZE_CHECK( sc.count() == 0 && ! sc.contains( '\0' ) ) ;
    }

    //      complement()
    // -----------------------------------------------------------------------
    {
        std::string s( "ab" ) ;
        set_of_chars        sc( s.cbegin(), s.cend() ) ;
        sc.complement() ;
        for ( int c = CHAR_MIN ; c <= CHAR_MAX ; ++ c ) {
            BREEZE_CHECK( sc.contains( static_cast< char >( c ) ) ==
                ( s.find( static_cast< char>( c ) ) == std::string::npos ) ) ;
        }
    }

    //      as_string()
    // -----------------------------------------------------------------------
    {
        std::string const   s =         "cage" ;
        std::string const   s_ordered = "aceg" ;
        set_of_chars const  sc( s ) ;

        BREEZE_CHECK( sc.as_string() == s_ordered ) ;
    }

    //      count()
    // -----------------------------------------------------------------------
    {
        set_of_chars        sc ;
        BREEZE_CHECK( sc.count() == 0 ) ;
        sc.add( "12345" ) ;
        BREEZE_CHECK( sc.count() == 5 ) ;
        sc.add( '6' ) ;
        BREEZE_CHECK( sc.count() == 6 ) ;
        sc.remove( "64253" ) ;
        BREEZE_CHECK( sc.count() == 1 && sc.contains( '1' ) ) ;

    }

    //      is_empty()
    // -----------------------------------------------------------------------
    {
        set_of_chars        sc ;
        BREEZE_CHECK( sc.is_empty() ) ;
        sc.add( "" ) ;
        BREEZE_CHECK( sc.is_empty() ) ;
        sc.add( 'x' ) ;
        BREEZE_CHECK( ! sc.is_empty() ) ;

    }

    //      Iterators.
    // -----------------------------------------------------------------------
    {
        set_of_chars::iterator const
                            default_constructed_iterator ;
        set_of_chars        sc ;
        BREEZE_CHECK( sc.begin() == sc.end() ) ;
        BREEZE_CHECK( sc.end() == default_constructed_iterator ) ;
        BREEZE_CHECK( sc.cbegin() == sc.cend() ) ;
        sc.add( 'a' ) ;
        BREEZE_CHECK( *sc.begin() == 'a' ) ;
        BREEZE_CHECK( *sc.cbegin() == 'a' ) ;
        BREEZE_CHECK( sc.end() == default_constructed_iterator ) ;

        set_of_chars::iterator
                            beg = sc.begin() ;
        BREEZE_CHECK( ++ beg == sc.end() ) ;

        sc.add( 'b' ) ;

        set_of_chars::iterator
                            it = std::find( sc.cbegin(), sc.cend(), 'a' ) ;
        BREEZE_CHECK( * ( ++ it) == 'b' ) ;

        it = std::find( sc.begin(), sc.end(), 'b' ) ;
        BREEZE_CHECK(  it != sc.end() && *it == 'b' ) ;

        BREEZE_CHECK( ++ it == sc.end() ) ;

        int const           num = 2 ;
        char const          to_be_found[ num ] = { 'a', 'b' } ;
        it = std::search( sc.cbegin(), sc.cend(),
                          to_be_found, to_be_found + num ) ;
        BREEZE_CHECK( it == sc.cbegin() ) ;

        sc.remove( 'b' ) ;
        it = std::find( sc.begin(), sc.end(), 'a' ) ;
        BREEZE_CHECK( it == sc.begin() ) ;
        BREEZE_CHECK( it != sc.end() && *it == 'a' ) ;
        BREEZE_CHECK( std::find( sc.begin(), sc.end(), 'b' ) == sc.end() ) ;

        set_of_chars        sc_min ;
        sc_min.add( static_cast< char >( CHAR_MIN ) ) ;

        BREEZE_CHECK( sc_min.begin() != sc_min.end() ) ;
        BREEZE_CHECK( *sc_min.begin() == CHAR_MIN ) ;

        sc_min.remove( static_cast< char >( CHAR_MIN ) ) ;
        BREEZE_CHECK( sc_min.begin() == sc_min.end() ) ;

        set_of_chars        sc_max ;
        sc_max.add( static_cast< char >( CHAR_MAX ) ) ;

        BREEZE_CHECK( sc_max.begin() != sc_max.end() ) ;
        BREEZE_CHECK( *sc_max.begin() == CHAR_MAX ) ;

        sc_max.remove( CHAR_MAX ) ;
        BREEZE_CHECK( sc_max.begin() == sc_max.end() ) ;
    }
}

void
set_of_chars_can_be_constructed_from_input_iterators()
{
    std::istringstream  iss( "bca" ) ;
    breeze::set_of_chars
                        set(   std::istream_iterator< char >( iss ),
                             ( std::istream_iterator< char >() ) ) ;

    BREEZE_CHECK( set.as_string() == "abc" ) ;
}

}

int
test_set_of_chars()
{
    using namespace breeze ;

    return test_runner::instance().run(
             "set_of_chars",
             { do_test,
               set_of_chars_can_be_constructed_from_input_iterators } ) ;
}


// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
