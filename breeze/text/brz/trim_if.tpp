// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/text/trim_head_if.hpp"
#include "breeze/text/trim_tail_if.hpp"

namespace breeze_ns {

template< typename Predicate >
std::string
trim_if( std::string const & str, Predicate pred )
{
    return breeze::trim_tail_if( breeze::trim_head_if( str, pred ), pred ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
