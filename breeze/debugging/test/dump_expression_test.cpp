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

#include "breeze/debugging/dump_expression.hpp"
#include "breeze/testing/testing.hpp"
#include <iostream>
#include <ostream> // not necessary in C++11
#include <sstream>
#include <streambuf>

int                 test_breeze_dump_expression() ;

namespace {

//      "Captures" the output of 'os' to the streambuf pointed to by
//      'buf'. Restores 'os' in the destructor. Used to "capture" the
//      output to std::cout into a stringstream.
// ---------------------------------------------------------------------------
class stream_capturer
{
public:
                        stream_capturer( stream_capturer const & ) = delete ;
    stream_capturer &   operator =(      stream_capturer const & ) = delete ;

    explicit            stream_capturer( std::ostream & os,
                                         std::streambuf * buf )
                            :   m_os( os ), m_oldbuf( os.rdbuf( buf ) )
                        {
                        }

                        ~stream_capturer() noexcept
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

void
do_test()
{
    std::ostringstream  oss ;
    stream_capturer const
                        capturer( std::cout, oss.rdbuf() ) ;

    //      Check that 1 << 3 is output as "1 << 3", first, and not
    //      directly as "8"
    // -----------------------------------------------------------------------
    BREEZE_DUMP_EXPRESSION( 1 << 3 ) ;
    BREEZE_CHECK( oss.str() == "1 << 3 = 8\n" ) ;
    clear_stringstream( oss ) ;

    //      Check that macros are expanded (the replacement lists here
    //      are intentionally not parenthesized, although we already
    //      have a separate parenthesis-test in place).
    // -----------------------------------------------------------------------
#   define OBJECT_LIKE_DUMMY        1 << 3 * 2
#   define FUNCTION_LIKE_DUMMY()    1 << 3 * 4

    BREEZE_DUMP_EXPRESSION( OBJECT_LIKE_DUMMY ) ;
    BREEZE_CHECK( oss.str() == "1 << 3 * 2 = 64 [from: OBJECT_LIKE_DUMMY]\n" ) ;
    clear_stringstream( oss ) ;

    BREEZE_DUMP_EXPRESSION( FUNCTION_LIKE_DUMMY() ) ;
    BREEZE_CHECK( oss.str() ==
             "1 << 3 * 4 = 4096 [from: FUNCTION_LIKE_DUMMY()]\n" ) ;
    clear_stringstream( oss ) ;
}

}

int
test_breeze_dump_expression()
{
    return breeze::test_runner::instance().run(
             "BREEZE_DUMP_EXPRESSION()",
             { do_test } ) ;
}
