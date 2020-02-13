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

#include "breath/text/to_lowercase.hpp"

namespace breath {

std::string
to_lowercase( std::string const & source, std::locale const & loc )
{
    std::string         result ;
    result.reserve( source.size() ) ;

    //      We could use std::transform() with std::back_inserter(),
    //      here; but I'm not sure that would really improve anything.
    //
    //      (But if you change this, change to_uppercase(), as well.)
    // -----------------------------------------------------------------------
    for ( char const c : source ) {
        result += std::tolower( c, loc ) ;
    }

    return result ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
