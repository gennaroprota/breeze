// =========================================================================
//                This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// =========================================================================
//                       Copyright 2017 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#include "breath/metric/levenshtein_distance.hpp"
#include <algorithm>
#include <numeric>
#include <vector>

namespace breath {

std::size_t
levenshtein_distance( std::string const & first, std::string const & second )
{
    std::size_t const   len1 = first.length() ;
    std::size_t const   len2 = second.length() ;

    std::vector< std::size_t > costs( len2 + 1 ) ;
    std::iota( costs.begin(), costs.end(), 0 ) ;

    for ( std::size_t i = 0 ; i < len1 ; ++ i ) {
        costs[ 0 ] = i + 1 ;
        size_t              corner = i ;

        for ( std::size_t j = 0 ; j < len2 ; ++ j ) {
            size_t const        upper = costs[ j + 1 ] ;
            costs[ j + 1 ] = first[ i ] == second[ j ]
                               ? corner
                               : 1 + (std::min)( { upper, corner, costs[ j ] } )
                               ;
            corner = upper ;
        }
    }

    return costs[ len2 ] ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
