// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2016-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/text/trim.hpp"
#include "breeze/text/trim_head.hpp"
#include "breeze/text/trim_tail.hpp"

namespace breeze_ns {

std::string
trim( std::string const & s, std::locale const & loc )
{
    return breeze::trim_tail( breeze::trim_head( s, loc ), loc ) ;
}

std::string
trim( std::string const & s, set_of_chars const & to_be_removed )
{
    return breeze::trim_tail(
        breeze::trim_head( s, to_be_removed ), to_be_removed ) ;
}

}
