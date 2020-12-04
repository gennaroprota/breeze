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

#include "breeze/testing/stream_reporter.hpp"
#include "breeze/testing/test_exception.hpp"
#include <ostream>
#include <string>
#include <typeinfo>

namespace breeze_ns {

stream_reporter::stream_reporter( std::ostream & os )
    :   m_stream( os ),
        m_passed( 0 ),
        m_failed( 0 ),
        m_unexpected_exceptions( 0 )
{
}

void
stream_reporter::do_on_all_tests_begin( char const * group_description )
{
    std::string const   extra_text = ":" ;
    std::string const   description = group_description + extra_text ;
    std::string const   ruler( description.length(), '-' ) ;
    m_stream << description << '\n' <<
                ruler << std::endl ;
}

void
stream_reporter::do_on_all_tests_end()
{
    m_stream << std::endl << "Passed: " << m_passed << ", failed: " << m_failed
                          << ", unexp. exceptions: " << m_unexpected_exceptions
                          << '\n' << std::endl ;

    m_passed = 0 ;
    m_failed = 0 ;
    m_unexpected_exceptions = 0 ;
}

void
stream_reporter::do_on_test_begin( int test_number, char const * )
{
    m_stream << '[' << test_number << '=' ;
    m_stream.flush() ;
}

void
stream_reporter::do_on_test_passed( int )
{
    m_stream << "P]" ;
    m_stream.flush() ;
    ++ m_passed ;
}

void
stream_reporter::do_on_test_failed( int, test_exception const & ex )
{
    m_stream << "F (" << ex << ")]" ;
    m_stream.flush() ;
    ++ m_failed ;
}

void
stream_reporter::do_on_unexpected_exception( int )
{
    m_stream << "X]" ;
    m_stream.flush() ;
    ++ m_unexpected_exceptions ;
}

void
stream_reporter::do_on_unexpected_exception( int,
                                           std::exception const & ex )
{
    m_stream << "X (" << typeid( ex ).name() << ": " << ex.what() << ")]" ;
    m_stream.flush() ;
    ++ m_unexpected_exceptions ;
}

}
