// =========================================================================
//                This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/testing/test_descriptor.hpp"

namespace breath {

test_descriptor::test_descriptor( void( &f )(), char const * name ) noexcept
    :   m_function( f ),
        m_name( name )
{
}

test_descriptor::test_function
test_descriptor::function() const noexcept
{
    return m_function ;
}

std::string
test_descriptor::name() const noexcept
{
    return m_name ;
}
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
