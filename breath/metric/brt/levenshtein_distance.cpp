// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/metric/levenshtein_distance.hpp"
#include <algorithm>
#include <numeric>
#include <vector>

namespace breath {

std::ptrdiff_t
levenshtein_distance( std::string const & first, std::string const & second )
{
    typedef std::ptrdiff_t
                        length_type ;

    length_type const   len1 = first.length() ;
    length_type const   len2 = second.length() ;

    std::vector< length_type > costs( len2 + 1 ) ;
    std::iota( costs.begin(), costs.end(), 0 ) ;

    for ( length_type i = 0 ; i < len1 ; ++ i ) {
        costs[ 0 ] = i + 1 ;
        length_type         corner = i ;

        for ( length_type j = 0 ; j < len2 ; ++ j ) {
            length_type const   upper = costs[ j + 1 ] ;
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
