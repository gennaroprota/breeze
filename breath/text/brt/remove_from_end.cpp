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

#include "breath/text/remove_from_end.hpp"
#include "breath/text/ends_with.hpp"

namespace breath {

std::string
remove_from_end( std::string const & str, std::string const & to_be_removed )
{
    auto                copy( str ) ;
    if ( breath::ends_with( copy, to_be_removed ) ) {
        copy.erase( copy.end() - to_be_removed.length(), copy.end() ) ;
    }
    return copy ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
