// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include <algorithm>

namespace breeze_ns {

template< typename UnaryPredicate >
std::vector< std::string >
split_if( std::string const & s, UnaryPredicate pred )
{
    std::vector< std::string >
                        result ;
    auto                start = s.cbegin() ;
    auto                end   = std::find_if( start, s.cend(), pred ) ;
    result.emplace_back( start, end ) ;
    while ( end != s.cend() ) {
        start = end + 1 ;
        end = std::find_if( start, s.cend(), pred ) ;
        result.emplace_back( start, end ) ;
    }

    return result ;
}

}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
