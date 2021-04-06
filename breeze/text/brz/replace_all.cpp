// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/text/replace_all.hpp"
#include "breeze/diagnostics/assert.hpp"
#include <algorithm>
#include <string>

namespace breeze_ns {

std::string
replace_all(
    std::string const & original,
    std::string const & from,
    std::string const & to )
{
    BREEZE_ASSERT( ! from.empty() ) ;

    std::string         result ;

    std::string::const_iterator
                        current = original.cbegin() ;
    std::string::const_iterator const
                        end = original.cend() ;
    std::string::const_iterator
                        next = std::search( current, end, from.cbegin(),
                                 from.cend() ) ;
    while ( next != end ) {
        result.append( current, next ) ;
        result.append( to ) ;
        current = next + from.size() ;
        next = std::search( current, end, from.cbegin(), from.cend() ) ;
    }

    result.append( current, end ) ;
    return result ;
}

}
