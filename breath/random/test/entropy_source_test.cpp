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

#include "breath/random/entropy_source.hpp"
#include <cstdlib>

int                 test_entropy_source() ;

int
test_entropy_source()
{
    breath::entropy_source
                        source ;

    int                 result = EXIT_FAILURE ;

    if (source.release()) {
        // check that a second release doesn't yield "success"
        //
        if ( ! source.release() ) {
            result = EXIT_SUCCESS ;
        }
    }

    return result ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
