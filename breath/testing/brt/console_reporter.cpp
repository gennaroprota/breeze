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

#include "breath/testing/console_reporter.hpp"
#include "breath/testing/test_exception.hpp"
#include <ostream>
#include <string>
#include <typeinfo>

namespace breath {

console_reporter::console_reporter( std::ostream & os )
    :   m_stream( os ),
        m_passed( 0 ),
        m_failed( 0 ),
        m_unexpected_exceptions( 0 )
{
}

void
console_reporter::do_on_all_tests_begin( char const * group_description )
{
    std::string const   extra_text = ":" ;
    std::string const   description = group_description + extra_text ;
    std::string const   ruler( description.length(), '-' ) ;
    m_stream << description << '\n' <<
                ruler << std::endl ;
}

void
console_reporter::do_on_all_tests_end()
{
    m_stream << std::endl << "Passed: " << m_passed << ", failed: " << m_failed
                          << ", unexp. exceptions: " << m_unexpected_exceptions
                          << '\n' << std::endl ;
}

void
console_reporter::do_on_test_begin( int test_number, char const * )
{
    m_stream << '[' << test_number << '=' ;
}

void
console_reporter::do_on_test_passed( int )
{
    m_stream << "P]" ;
    ++ m_passed ;
}

void
console_reporter::do_on_test_failed(int, test_exception const & ex )
{
    m_stream << "F (" << ex.file_name() << ": " << ex.line_number() << ")]" ;
    ++ m_failed ;
}

void
console_reporter::do_on_unexpected_exception( int )
{
    m_stream << "X]" ;
    ++ m_unexpected_exceptions ;
}

void
console_reporter::do_on_unexpected_exception( int,
                                           std::exception const & ex )
{
    m_stream << "X (" << typeid( ex ).name() << ": " << ex.what() << ")]" ;
    ++ m_unexpected_exceptions ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
