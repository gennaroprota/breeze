// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include <algorithm>

namespace breath_ns {

template< typename Predicate >
std::string
trim_tail_if( std::string const & str, Predicate pred )
{
    return std::string(
             str.cbegin(),
             std::find_if_not( str.crbegin(), str.crend(), pred ).base() ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
