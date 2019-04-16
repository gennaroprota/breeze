// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2006-2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/path/extension.hpp"
#include "breath/path/allowed_path_separators.hpp"

namespace breath {

std::string
extension( std::string const & path )
{
    auto const          last_sep = path.find_last_of(
                            breath::allowed_path_separators()
                        ) ;

    // Note that last_sep can equal npos or path.size() - 1; in both
    // cases, adding 1 is OK (see the preconditions of substr()).
    // -----------------------------------------------------------------------
    std::string const   last_name = path.substr( last_sep + 1 ) ;

    auto const          pos = last_name.rfind( '.' ) ;
    return pos == std::string::npos ||
           pos == 0                 ||
           last_name == ".."
        ? ""
        : last_name.substr( pos )
        ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
