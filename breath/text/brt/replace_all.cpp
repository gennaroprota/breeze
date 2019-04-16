// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/text/replace_all.hpp"
#include "breath/diagnostics/assert.hpp"
#include <string>

namespace breath {

void replace_all(
    std::string & s,
    std::string const & from,
    std::string const & to )
{
    BREATH_ASSERT( ! from.empty() ) ;

    std::string::size_type pos = 0 ;

    //      Note that 'pos', below, may reach s.size(): this happens
    //      (only) when 's' is empty (pos == 0) or when a replacement
    //      occurs at the end of 's' (see the statement
    //
    //        'pos += to.length()'
    //
    //      ). This is fine, because find() has no preconditions and
    //      handles that case correctly.
    // ---------------------------------------------------------------------
    while ( (pos = s.find( from, pos )) != s.npos ) {
        s.replace( pos, from.length(), to ) ;
        pos += to.length() ;
    }
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
