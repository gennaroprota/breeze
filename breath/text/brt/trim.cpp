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

#include "breath/text/trim.hpp"
#include "breath/text/trim_head.hpp"
#include "breath/text/trim_tail.hpp"

namespace breath {

std::string
trim( std::string const & str, std::locale const & loc )
{
    return breath::trim_tail( breath::trim_head( str, loc ), loc ) ;
}

std::string
trim( std::string const & str, set_of_chars const & to_remove )
{
    return breath::trim_tail( breath::trim_head( str, to_remove ), to_remove ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
