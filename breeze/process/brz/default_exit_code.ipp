// ===========================================================================
//                        Copyright 2021 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//      Exit codes suitable at least for Windows and Unix.
//
//      Rationale:
//      ----------
//
//       - `exit_warning` is defined to 0, because treating a different
//         value as success in a shell script is too difficult
//
//       - on POSIX conforming systems, "only the least significant 8
//         bits (that is, status & 0377) shall be available to a waiting
//         parent process", so stay below 256
//
//       - on Unix systems many de facto conventions exist and it is
//         generally better to stay below 64 anyway
//
//       - the values are not consecutive, so that we can add
//         enumerators, if needed, without changing the values of the
//         subsequent ones
// ---------------------------------------------------------------------------

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

enum exit_code
{
    exit_success  =  0,
    exit_warning  = exit_success,
    exit_error    = 20,
    exit_fatal    = 30,
    exit_internal = 50
} ;

}
