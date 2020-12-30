// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2010 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/process/exit_code.hpp"
#include "breeze/porting/dependent_source.hpp"
#include BREEZE_DEPENDENT_SOURCE( system, exit_code.cpp )
#include <cstdlib>

namespace breeze_ns {

//      These two can be specified portably, so we define them outside
//      of the system-dependent exit_code.cpp's.
// ---------------------------------------------------------------------------
extern int const    exit_success = 0 ;
extern int const    exit_failure = EXIT_FAILURE ;

}
