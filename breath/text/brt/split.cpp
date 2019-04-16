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

namespace breath {

std::vector< std::string >
split( std::string const & s, std::string const & delimiters )
{
    BREATH_ASSERT( s.size() < std::size_t( - 1 ) ) ;

    std::vector< std::string >
                        result ;

    //      Note:
    //          The <= (in lieu of <) in the for condition is
    //          intentional (note that find_first_of() has no
    //          preconditions).
    //
    //          In theory, this is susceptible of an infinite loop, but
    //          this would only occur with a string of std::size_t( -1 )
    //          characters, which we do not support.
    // ---------------------------------------------------------------------
    for ( std::size_t i = 0 ; i <= s.size() ; ++ i ) {
        auto const          start = i ;
        i = s.find_first_of( delimiters, i );
        if ( i == s.npos ) {
            i = s.size() ;
        }
        result.emplace_back( s.cbegin() + start, s.cbegin() + i ) ;
    }
    return result ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
