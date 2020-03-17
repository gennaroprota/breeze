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

#include "breath/meta/is_twos_complement.hpp"

using breath::meta::is_twos_complement ;

//      TODO: use our test facilities anyway, to have a run-time report?
//
static_assert( ! is_twos_complement< bool >(),          "" ) ;
static_assert(   is_twos_complement< signed char >(),   "" ) ;
static_assert( ! is_twos_complement< unsigned char >(), "" ) ;

static_assert(   is_twos_complement< int >(),           "" ) ;
static_assert( ! is_twos_complement< unsigned int >(),  "" ) ;

int
main()
{
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
