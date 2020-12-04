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

#include "breeze/testing/test_descriptor.hpp"

namespace breeze_ns {

test_descriptor::test_descriptor( test_function f, char const * name )
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
test_descriptor::name() const
{
    return m_name ;
}
}
