// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/path/base_file_name.hpp"
#include "breath/path/allowed_path_separators.hpp"
#include <string>

namespace breath {

std::string
base_file_name( std:: string const & full_path)
{
    std::string::size_type const
                        pos = full_path.find_last_of(
                                breath::allowed_path_separators() ) ;
    return pos == std::string::npos
                    ? full_path
                    : full_path.substr( pos + 1 )
                    ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
