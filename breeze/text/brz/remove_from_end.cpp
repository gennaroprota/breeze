// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2013 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/text/remove_from_end.hpp"
#include "breeze/text/ends_with.hpp"

namespace breeze_ns {

std::string
remove_from_end( std::string const & s, std::string const & to_be_removed )
{
    return breeze::ends_with( s, to_be_removed )
        ? s.substr( 0, s.length() - to_be_removed.length() )
        : s
        ;
}

std::string
remove_from_end( std::string const & s, char c )
{
    return breeze::ends_with( s, c )
        ? s.substr( 0, s.length() - 1 )
        : s
        ;
}

}
