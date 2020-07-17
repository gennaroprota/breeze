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

#include "breath/idiom/declare_non_copyable.hpp"
#include "breath/testing/testing.hpp"
#include "breath/text/from_string.hpp"
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

int                 test_from_string() ;

namespace {

template< typename T >
bool
is_expected( std::string const & s, T expected )
{
    auto const          m = breath::from_string< T >( s ) ;
    return m.is_valid() && m.value() == expected ;
}

void do_tests()
{
    BREATH_CHECK( ! breath::from_string< int >( "   " ).is_valid() ) ;
    BREATH_CHECK( is_expected< int >( "12", 12 ) ) ;
    BREATH_CHECK( is_expected< int >( "12   \t", 12 ) ) ;
    BREATH_CHECK( ! breath::from_string< int >( "12 1" ).is_valid() ) ;
    BREATH_CHECK( is_expected< char >( "a", 'a' ) ) ;
    BREATH_CHECK( is_expected< char >( " a ", 'a' ) ) ;
    BREATH_CHECK( ! breath::from_string< char >( "ab" ).is_valid() ) ;
    BREATH_CHECK( is_expected< double >( "1.2", 1.2 ) ) ;

    BREATH_CHECK( is_expected< std::string >( " test ", " test " ) ) ;
    BREATH_CHECK( is_expected< std::string >( " multiple words ",
                                                      " multiple words ") ) ;
    BREATH_CHECK( is_expected< std::string >( "", "" ) ) ;
}

class move_only final
{
    std::string         m_s ;

public:
    BREATH_DECLARE_NON_COPYABLE( move_only )

                        move_only()                     = default ;
                        move_only( move_only && other ) = default ;
    move_only &         operator =( move_only && rhs )  = default ;

    std::string         get() const { return m_s; }

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
    auto const &        m = breath::from_string< move_only >( "test" ) ;
    BREATH_CHECK( m.is_valid() && m.value().get() == "test" ) ;
}

}

int
test_from_string()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( "from_string()",
                                        { do_tests, test_move_only } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
