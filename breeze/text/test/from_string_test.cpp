// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2016-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/testing/testing.hpp"
#include "breeze/text/from_string.hpp"
#include <istream>
#include <sstream>
#include <string>

int                 test_from_string() ;

namespace {

template< typename T >
bool
is_expected( std::string const & s, T expected )
{
    breeze::maybe< T > const
                        m = breeze::from_string< T >( s ) ;
    return m.is_valid() && m.value() == expected ;
}

void do_tests()
{
    BREEZE_CHECK( ! breeze::from_string< int >( "   " ).is_valid() ) ;
    BREEZE_CHECK( is_expected< int >( "12", 12 ) ) ;
    BREEZE_CHECK( is_expected< int >( "12   \t", 12 ) ) ;
    BREEZE_CHECK( ! breeze::from_string< int >( "12 1" ).is_valid() ) ;
    BREEZE_CHECK( is_expected< char >( "a", 'a' ) ) ;
    BREEZE_CHECK( is_expected< char >( " a ", 'a' ) ) ;
    BREEZE_CHECK( ! breeze::from_string< char >( "ab" ).is_valid() ) ;

    //      Note: don't just do
    //
    //        BREEZE_CHECK( is_expected< double >( "1.2", 1.2 ) ) ;
    //
    //      because that would compare two floating points, giving a
    //      -Wfloat-equal warning with GCC (and Clang?).
    // -----------------------------------------------------------------------
    std::ostringstream  oss ;
    breeze::maybe< double > const
                        m = breeze::from_string< double >( "1.2" ) ;
    BREEZE_CHECK( m.is_valid() ) ;
    oss << m.value() ;
    BREEZE_CHECK( oss.str() == "1.2" ) ;

    BREEZE_CHECK( is_expected< std::string >( " test ", " test " ) ) ;
    BREEZE_CHECK( is_expected< std::string >( " multiple words ",
                                                      " multiple words ") ) ;
    BREEZE_CHECK( is_expected< std::string >( "", "" ) ) ;
}

class move_only final
{
    std::string         m_s ;

public:
                        move_only(  move_only const & ) = delete ;
    move_only &         operator =( move_only const & ) = delete ;

                        move_only()                     = default ;
                        move_only( move_only && other ) = default ;

    std::string         get() const { return m_s ; }

    friend std::istream &
                        operator >>( std::istream &, move_only & ) ;
} ;

std::istream &
operator >>( std::istream & is, move_only & m )
{
    return is >> m.m_s ;
}

void
test_move_only()
{
    breeze::maybe< move_only > const
                        m = breeze::from_string< move_only >( "test" ) ;
    BREEZE_CHECK( m.is_valid() && m.value().get() == "test" ) ;
}

}

int
test_from_string()
{
    return breeze::test_runner::instance().run(
        "from_string()",
        { do_tests, test_move_only } ) ;
}
