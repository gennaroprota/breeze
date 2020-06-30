// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2006-2010 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

namespace breath_ns {

//      Note:
//          this currently uses the same values as the Unix variant, as
//          there's no reason to do otherwise and that might simplify
//          cross-platform scripts.
// ---------------------------------------------------------------------------
int const           exit_warning  = 10 ;
int const           exit_error    = 20 ;
int const           exit_fatal    = 30 ;
int const           exit_internal = 50 ;

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
