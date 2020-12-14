// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/diagnostics/last_api_error.hpp"
#include "breeze/porting/dependent_code.hpp"
#include BREEZE_DEPENDENT_CODE( system, last_api_error.cpp )

#include <ostream>

namespace breeze_ns {

long long
last_api_error::code() const noexcept
{
    return m_code ;
}

std::ostream &
operator <<( std::ostream & dest, last_api_error const & last )
{
    return dest << last.what() << " [code: " << last.code() << ']' ;
}

}
