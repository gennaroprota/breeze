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
#include "breeze/porting/dependent_source.hpp"
#include BREEZE_DEPENDENT_SOURCE( system_family, last_api_error.cpp )

#include <ostream>
#include <sstream>
#include <stdexcept>

namespace breeze_ns {

long long
last_api_error::code() const noexcept
{
    return m_code ;
}

std::string
last_api_error::to_string() const
{
    std::ostringstream  oss ;
    oss << what() << " [code: " << code() << ']' ;

    if ( oss.fail() ) {
        throw std::runtime_error(
            "error in last_api_error::to_string()" ) ;
    }

    return oss.str() ;
}

std::ostream &
operator <<( std::ostream & dest, last_api_error const & last )
{
    return dest << last.to_string() ;
}

}
