// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/vocabulary/maybe.hpp"
#include "breeze/testing/testing.hpp"
#include <string>
#include <utility>

int                 test_maybe() ;

namespace {

void
check_constructors()
{
    using breeze::maybe ;

    // default constructor
    {
        maybe< int >    m ;
        BREEZE_CHECK( ! m.is_valid() ) ;
    }

    // ordinary constructor
    {
        std::string const   s( "Hello" ) ;
        maybe< std::string >
                            m( s ) ;
        BREEZE_CHECK( m.is_valid() && m.value() == "Hello" ) ;
    }

    // copy constructor
    {
        maybe< std::string > invalid ;
        maybe< std::string > m( invalid ) ;
        BREEZE_CHECK( ! m.is_valid() ) ;

        maybe< std::string > valid( "foo" ) ;
        maybe< std::string > m2( valid) ;

        BREEZE_CHECK( m2.is_valid() && m2.value() == "foo" ) ;
    }

    // move constructor
    {
        std::string         s = "Hello" ;
        maybe< std::string > m( s ) ;
        maybe< std::string > m2 = std::move( m ) ;
        BREEZE_CHECK( m2.is_valid() && m2.value() == "Hello" ) ;
        BREEZE_CHECK( m.is_valid() ) ;
    }

    // constructor from T &&
    {
        maybe< std::string > m( "Hello" ) ; // from temporary
        BREEZE_CHECK( m.is_valid() && m.value() == "Hello" ) ;
    }
}

void
check_assignments()
{
    using breeze::maybe ;

    // copy assignment operator
    {
        maybe< int >        m ;
        maybe< int >        invalid ;
        maybe< int >        valid( 1 ) ;
        m = invalid ;
        BREEZE_CHECK( ! m.is_valid() ) ;
        m = valid ;
        BREEZE_CHECK( m.is_valid() && m.value() == 1 ) ;
        m = invalid ;
        BREEZE_CHECK( ! m.is_valid() ) ;
        // The following double assignment is intentional
        m = valid ;
        m = valid ;
        BREEZE_CHECK( m.is_valid() && m.value() == 1 ) ;
    }

    // operator =( T const & )
    {
        std::string          s = "Hello" ;
        std::string          t = "world" ;
        maybe< std::string > m ;
        m = s ;
        BREEZE_CHECK( m.is_valid() && m.value() == "Hello" ) ;
        m = t ;
        BREEZE_CHECK( m.is_valid() && m.value() == "world" ) ;
    }

    // move assignment operator
    {
        maybe< std::string > m ;
        maybe< std::string > m2 ;
        maybe< std::string > m3( "Ciao" ) ;
        m = std::move( m2 ) ; // invalid -> invalid
        BREEZE_CHECK( ! m.is_valid() ) ;
        BREEZE_CHECK( ! m2.is_valid() ) ;
        m = std::move( m3 ) ; // valid -> invalid
        BREEZE_CHECK( m.is_valid() && m.value() == "Ciao" ) ;
        BREEZE_CHECK( m3.is_valid() ) ;
        maybe< std::string > m4 ;
        m = std::move( m4 ) ; // invalid -> valid
        BREEZE_CHECK( ! m.is_valid() ) ;
        BREEZE_CHECK( ! m4.is_valid() ) ;
        maybe< std::string > m5( "mondo" ) ;
        maybe< std::string > m6( "!" ) ;
        // The following double assignment is intentional
        m = m5 ;
        m = std::move( m6 ) ; // valid -> valid
        BREEZE_CHECK( m.is_valid() && m.value() == "!" ) ;
        BREEZE_CHECK( m6.is_valid() ) ;
    }

    // operator =( T && )
    {
        maybe< std::string > m ;
        m = "Hello" ; // from temporary
        BREEZE_CHECK( m.is_valid() && m.value() == "Hello" ) ;
        m = "world" ;
        BREEZE_CHECK( m.is_valid() && m.value() == "world" ) ;
    }
}

}

int
test_maybe()
{
    using namespace breeze ;

    return test_runner::instance().run( "maybe",
                                   { check_constructors, check_assignments } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
