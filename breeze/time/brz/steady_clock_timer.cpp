// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/time/steady_clock_timer.hpp"

namespace breeze_ns {

steady_clock_policy::steady_clock_policy() = default ;

void
steady_clock_policy::start() noexcept
{
    m_start_time = std::chrono::steady_clock::now() ;
}

steady_clock_policy::duration_type
steady_clock_policy::elapsed() const noexcept
{
    auto const          now = std::chrono::steady_clock::now() ;
    return now - m_start_time ;
}

}
