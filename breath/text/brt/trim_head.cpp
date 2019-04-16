// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/text/trim_head.hpp"
#include "breath/text/set_of_chars.hpp"

namespace breath {

std::string
trim_head( std::string const & str )
{
    return breath::trim_head( str, set_of_chars( " \f\n\r\t\v" ) ) ;
}

std::string
trim_head( std::string const & source, set_of_chars const & to_remove )
{
    auto const          pos =
        source.find_first_not_of( to_remove.as_string() ) ;
    return pos == std::string::npos
        ? ""
        : std::string( source, pos )
        ;


}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
