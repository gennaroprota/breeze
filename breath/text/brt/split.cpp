// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2008-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/text/split.hpp"
#include "breath/diagnostics/assert.hpp"
#include <cstddef>

namespace breath_ns {

std::vector< std::string >
split( std::string const & s, std::string const & separators )
{
    std::vector< std::string >
                        result ;

    std::string::size_type
                        start = 0 ;
    std::string::size_type
                        end   = 0 ;
    while ( start < s.size() && end != s.npos ) {
        end = s.find_first_of( separators, start );
        if ( end != s.npos ) {
            result.emplace_back( s.cbegin() + start, s.cbegin() + end ) ;
            start = end + 1 ;
        }
    }

    result.emplace_back( s.cbegin() + start, s.cend() ) ;
    return result ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
