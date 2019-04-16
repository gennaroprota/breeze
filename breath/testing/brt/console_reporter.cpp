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
console_reporter::on_all_tests_begin()
{
    m_stream << "Unit tests:" << std::endl ;
}

void
console_reporter::on_all_tests_end()
{
    m_stream << std::endl << "Passed: " << m_passed << ", failed: " << m_failed
                          << ", unexp. exceptions: " << m_unexpected_exceptions
                          << std::endl ;
}

void
console_reporter::on_test_begin( std::size_t test_number, char const * )
{
    m_stream << '[' << test_number << '=' ;
}

void
console_reporter::on_test_passed( std::size_t )
{
    m_stream << "P]" ;
    ++ m_passed ;
}

void
console_reporter::on_test_failed( std::size_t, test_exception const & ex )
{
    m_stream << "F (" << ex.file_name() << ": " << ex.line() << ")]" ;
    ++ m_failed ;
}

void
console_reporter::on_unexpected_exception( std::size_t )
{
    m_stream << "X]" ;
    ++ m_unexpected_exceptions ;
}

void
console_reporter::on_unexpected_exception( std::size_t,
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
