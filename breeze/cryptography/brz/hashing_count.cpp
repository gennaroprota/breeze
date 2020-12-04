// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2006-2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/cryptography/hashing_count.hpp"

namespace breeze_ns {

hashing_count::exception::exception( char const * message )
    : std::length_error( message )
{
}

void
hashing_count::on_length_exhausted( hashing_count::type t )
{
    if ( t == hashing_count::is_limited ) {
        throw hashing_count::exception(
                "input too long for this hash function" ) ;
    }
}

}
