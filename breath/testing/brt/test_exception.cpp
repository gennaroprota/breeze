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

#include "breath/testing/test_exception.hpp"

namespace breath {

test_exception::test_exception( char const * file_name,
                                unsigned long line ) noexcept
    :   exception(),
        m_file_name( file_name ),
        m_line( line )
{
}

test_exception::test_exception( std::string const & message,
                                char const * file_name,
                                unsigned long line ) noexcept
    :   exception( message ),
        m_file_name( file_name ),
        m_line( line )
{
}

char const *
test_exception::file_name() const noexcept
{
    return m_file_name ;
}

unsigned long
test_exception::line() const noexcept
{
    return m_line ;
}

std::ostream &
operator <<(std::ostream & os, test_exception const & ex )
{
    return os << ex.what() << ": " << ex.file_name() << ", " << ex.line() ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
