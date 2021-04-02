// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2006-2007 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/cryptography/sha224.hpp"
#include "breeze/cryptography/sha256.hpp"

namespace breeze_ns {

void
sha224_engine::init_state( state_type & state )
{
        state[ 0 ] = 0xc1059ed8 ;
        state[ 1 ] = 0x367cd507 ;
        state[ 2 ] = 0x3070dd17 ;
        state[ 3 ] = 0xf70e5939 ;
        state[ 4 ] = 0xffc00b31 ;
        state[ 5 ] = 0x68581511 ;
        state[ 6 ] = 0x64f98fa7 ;
        state[ 7 ] = 0xbefa4fa4 ;
}

void
sha224_engine::process_block( block_type const & block, state_type & state )
{
    return sha256_engine::process_block( block, state ) ;
}

}
