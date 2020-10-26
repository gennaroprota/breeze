// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include <algorithm>

namespace breath_ns {

template< typename UnaryPredicate >
std::vector< std::string >
split_if( std::string const & s, UnaryPredicate pred )
{
    std::vector< std::string >
                        result ;
    auto                start = s.cbegin() ;
    auto                end   = start ;
    while ( end != s.cend() ) {
        end = std::find_if( start, s.cend(), pred ) ;
        if ( end != s.cend() ) {
            result.emplace_back( start, end ) ;
            start = end + 1 ;
        }
    }

    result.emplace_back( start, s.cend() ) ;
    return result ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
