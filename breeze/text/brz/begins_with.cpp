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

#include "breeze/text/begins_with.hpp"
#include <algorithm>
#include <string>

namespace breeze_ns {

//      Note:
//          if 'with' is empty this always returns true. (Two empty
//          ranges always compare equal with std::equal(). To me, this
//          wasn't clear in the standard, but the committee said
//          otherwise; see:
//
//            <https://wg21.link/lwg2967>.
//
//          Of course, our unit tests verify that this is the case.)
// ---------------------------------------------------------------------------
bool
begins_with( std::string const & s, std::string const & with ) noexcept
{
    return s.size() >= with.size()
        && std::equal( with.cbegin(), with.cend(), s.cbegin() ) ;
}

bool
begins_with( std::string const & s, char c ) noexcept
{
    return ! s.empty() && s.front() == c ;
}

}
