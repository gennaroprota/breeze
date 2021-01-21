// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include <algorithm>

namespace breeze_ns {

template< typename Predicate >
std::string
trim_tail_if( std::string const & s, Predicate pred )
{
    return std::string(
             s.cbegin(),
             std::find_if_not( s.crbegin(), s.crend(), pred ).base() ) ;
}

}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
