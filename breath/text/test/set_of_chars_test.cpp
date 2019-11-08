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

#include "breath/text/set_of_chars.hpp"
#include <algorithm>
#include <climits>
////// gps
#include "breath/diagnostics/assert.hpp"
#define DO_TEST( x ) BREATH_ASSERT( x )
/////////////


int
main()
{
    using breath::set_of_chars ;

    //      Ordinary constructors.
    // -----------------------------------------------------------------------
    {
        set_of_chars const  sc1 ;
        DO_TEST( sc1.is_empty() ) ;

        set_of_chars const  sc2( "a" ) ;
        DO_TEST( sc2.contains( 'a' ) && sc2.count() == 1 ) ;

        std::string         str ;
        str.push_back( '\0' ) ;
        str.push_back( '\0' ) ;
        set_of_chars const  sc3( str ) ;
        DO_TEST( sc3.contains( '\0' ) && sc3.count() == 1 ) ;

        str.push_back( 'x' ) ;
        set_of_chars const sc4( str.cbegin(), str.cend() ) ;
        DO_TEST( sc4.contains( '\0' ) && sc4.contains( 'x')
                                        && sc4.count() == 2 ) ;

        {
            set_of_chars const
                            sc( set_of_chars::except, 'a' ) ;
            for( int n = CHAR_MIN ; n <= CHAR_MAX ; ++ n ) {
                DO_TEST( sc.contains( static_cast< char >( n ) ) ==
                                ( n != 'a' ) ) ;
            }
        }
    }

    //      Copy constructor.
    // -----------------------------------------------------------------------
    {
        set_of_chars const s("abcdefghijklmnopqrstuvwxyz") ;
        set_of_chars const t( s ) ;

        DO_TEST( t == s ) ;
        DO_TEST( t.as_string() == "abcdefghijklmnopqrstuvwxyz" ) ;
    }

    //      contains()
    // -----------------------------------------------------------------------
    {
        set_of_chars const  s( "wxyz") ;
        DO_TEST( s.contains( 'w' ) && s.contains( 'x' ) && s.contains( 'y' ) &&
            s.contains( 'z' ) && ! s.contains( 'a' ) && ! s.contains( '\0' ) ) ;
    }

    //      add() / remove()
    // -----------------------------------------------------------------------
    {
        DO_TEST( set_of_chars( "abc").add( 'd' ) == set_of_chars( "abcd" ) ) ;
        DO_TEST( set_of_chars( "abc").add( "d" ) == set_of_chars( "abcd" ) ) ;
    }
    {
        //      Check that we can add/remove a '\0'.
        // -------------------------------------------------------------------
        DO_TEST( set_of_chars( "" ).is_empty() ) ;
        std::string         s ;
        s.push_back( '\0' ) ;
        set_of_chars        sc ;
        sc.add( s ) ;
        DO_TEST( sc.count() == 1 && sc.contains('\0' ) ) ;
        sc.remove( s ) ;
        DO_TEST( sc.count() == 0 && ! sc.contains( '\0' ) ) ;
    }

    //      complement()
    // -----------------------------------------------------------------------
    {
        std::string s( "ab" ) ;
        set_of_chars        sc( s.cbegin(), s.cend() ) ;
        sc.complement() ;
        for ( int c = CHAR_MIN ; c <= CHAR_MAX ; ++ c ) {
            DO_TEST( sc.contains( static_cast< char >( c ) ) ==
                ( s.find( static_cast< char>( c ) ) == std::string::npos ) ) ;
        }
    }

    //      as_string()
    // -----------------------------------------------------------------------
    {
        std::string const   s =         "cage" ;
        std::string const   s_ordered = "aceg" ;
        set_of_chars const  sc( s ) ;

        DO_TEST( sc.as_string() == s_ordered ) ;
    }

    //      count()
    // -----------------------------------------------------------------------
    {
        set_of_chars        sc ;
        DO_TEST( sc.count() == 0 ) ;
        sc.add( "12345" ) ;
        DO_TEST( sc.count() == 5 ) ;
        sc.add( '6' ) ;
        DO_TEST( sc.count() == 6 ) ;
        sc.remove( "64253" ) ;
        DO_TEST( sc.count() == 1 && sc.contains( '1' ) ) ;

    }
    //      is_empty()
    // -----------------------------------------------------------------------
    {
        set_of_chars        sc ;
        DO_TEST( sc.is_empty() ) ;
        sc.add( "" ) ;
        DO_TEST( sc.is_empty() ) ;
        sc.add( 'x' ) ;
        DO_TEST( ! sc.is_empty() ) ;

    }

    //      Iterators.
    // -----------------------------------------------------------------------
    {
        set_of_chars::iterator
                            default_constructed_iterator ;
        set_of_chars        sc ;
        DO_TEST( sc.begin() == sc.end() ) ;
        DO_TEST( sc.end() == default_constructed_iterator ) ;
        DO_TEST( sc.cbegin() == sc.cend() ) ;
        sc.add( 'a' ) ;
        DO_TEST( *sc.begin() == 'a' ) ;
        DO_TEST( *sc.cbegin() == 'a' ) ;
        DO_TEST( sc.end() == default_constructed_iterator ) ;

        set_of_chars::iterator
                            beg = sc.begin() ;
        DO_TEST( ++ beg == sc.end() ) ;

        sc.add( 'b' ) ;

        set_of_chars::iterator
                            it = std::find( sc.cbegin(), sc.cend(), 'a' ) ;
        DO_TEST( * ( ++ it) == 'b' ) ;

        it = std::find( sc.begin(), sc.end(), 'b' ) ;
        DO_TEST(  it != sc.end() && *it == 'b' ) ;

        DO_TEST( ++ it == sc.end() ) ;

        sc.remove( 'b' ) ;
        it = std::find( sc.begin(), sc.end(), 'a' ) ;
        DO_TEST( it == sc.begin() ) ;
        DO_TEST( it != sc.end() && *it == 'a' ) ;
        DO_TEST( std::find( sc.begin(), sc.end(), 'b' ) == sc.end() ) ;

        set_of_chars        sc_min ;
        sc_min.add( static_cast< char >( CHAR_MIN ) ) ;

        DO_TEST( sc_min.begin() != sc_min.end() ) ;
        DO_TEST( *sc_min.begin() == CHAR_MIN ) ;

        sc_min.remove( static_cast< char >( CHAR_MIN ) ) ;
        DO_TEST( sc_min.begin() == sc_min.end() ) ;

        set_of_chars        sc_max ;
        sc_max.add( static_cast< char >( CHAR_MAX ) ) ;

        DO_TEST( sc_max.begin() != sc_max.end() ) ;
        DO_TEST( *sc_max.begin() == CHAR_MAX ) ;

        sc_max.remove( CHAR_MAX ) ;
        DO_TEST( sc_max.begin() == sc_max.end() ) ;
    }
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
