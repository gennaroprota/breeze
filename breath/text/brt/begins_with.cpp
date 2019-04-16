// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2013-2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/text/begins_with.hpp"
#include <algorithm>
#include <string>

namespace breath {

//      begins_with():
//      ==============
//
//      Note:
//          if 'with' is empty this always returns true. (Two empty
//          ranges always compare equal with std::equal. This wasn't
//          clear to me, but the committee said otherwise; see:
//
//            <https://wg21.link/lwg2967>.
//
//          Of course, our unit tests verify that this is the case.)
// -------------------------------------------------------------------------
bool
begins_with( std::string const & str, std::string const & with ) noexcept
{
    return str.size() >= with.size()
        && std::equal( with.cbegin(), with.cend(), str.cbegin() ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
