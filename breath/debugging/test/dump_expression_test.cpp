// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2013 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

// gps temp
#undef NDEBUG
#include <cassert>
#define DO_TEST(x)  assert(x)
// ^^^^^^^^ ---------------

#include "breath/debugging/dump_expression.hpp"
#include <cstdlib>
#include <iostream>
#include <ostream> // not necessary in C++11
#include <sstream>
#include <streambuf>

int                 test_breath_dump_expression() ;

namespace {

//      "Captures" the output of 'os' to the streambuf pointed to by
//      'buf'. Restores 'os' in the destructor. Used to "capture" the
//      output to std::cout into a stringstream.
// ---------------------------------------------------------------------------
class stream_guard
{
public:
    explicit            stream_guard( std::ostream & os, std::streambuf * buf )
                            :   m_os( os ), m_oldbuf( os.rdbuf( buf ) )
                        {
                        }

                        ~stream_guard() noexcept
                        {
                            m_os.rdbuf( m_oldbuf ) ;
                        }

private:
    std::ostream &      m_os ;
    std::streambuf *    m_oldbuf ;
} ;

void
clear_stringstream( std::ostringstream & ss )
{
    ss.str( "" ) ;
}

}

int
test_breath_dump_expression()
{
    std::ostringstream  oss ;
    stream_guard const  guard( std::cout, oss.rdbuf() ) ;

    //      Check that 1 << 3 is output as "1 << 3", first, and not
    //      directly as "8"
    // -----------------------------------------------------------------------
    BREATH_DUMP_EXPRESSION( 1 << 3 ) ;
    DO_TEST( oss.str() == "1 << 3 = 8\n" ) ;
    clear_stringstream( oss ) ;

    //      Check that macros are expanded (the replacement lists here
    //      are intentionally not parenthesized, although we already
    //      have a separate parenthesis-test in place).
    // -----------------------------------------------------------------------
#   define OBJECT_LIKE_DUMMY        1 << 3 * 2
#   define FUNCTION_LIKE_DUMMY()    1 << 3 * 4

    BREATH_DUMP_EXPRESSION( OBJECT_LIKE_DUMMY ) ;
    DO_TEST( oss.str() == "1 << 3 * 2 = 64 [from: OBJECT_LIKE_DUMMY]\n" ) ;
    clear_stringstream( oss ) ;

    BREATH_DUMP_EXPRESSION( FUNCTION_LIKE_DUMMY() ) ;
    DO_TEST( oss.str() ==
             "1 << 3 * 4 = 4096 [from: FUNCTION_LIKE_DUMMY()]\n" ) ;
    clear_stringstream( oss ) ;

    //      The one case that the macro doesn't detect: a macro that is
    //      object-like and expands to its own name (of course it's not
    //      important, but it's good to have a test here, in case I
    //      manage to detect it).
    // -----------------------------------------------------------------------
    int                             BREATH_dummy = 1 ;
#   define BREATH_dummy             BREATH_dummy

    BREATH_DUMP_EXPRESSION( BREATH_dummy ) ;
    DO_TEST( oss.str() == "BREATH_dummy = 1\n" ) ;
    clear_stringstream( oss ) ;

    return EXIT_SUCCESS ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
