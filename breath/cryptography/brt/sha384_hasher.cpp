// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/cryptography/sha384_hasher.hpp"
#include "breath/cryptography/sha512_hasher.hpp"

namespace breath {

void
sha384_engine::init_state( state_type & state )
{
    state[ 0 ] = 0xcbbb9d5dc1059ed8 ;
    state[ 1 ] = 0x629a292a367cd507 ;
    state[ 2 ] = 0x9159015a3070dd17 ;
    state[ 3 ] = 0x152fecd8f70e5939 ;
    state[ 4 ] = 0x67332667ffc00b31 ;
    state[ 5 ] = 0x8eb44a8768581511 ;
    state[ 6 ] = 0xdb0c2e0d64f98fa7 ;
    state[ 7 ] = 0x47b5481dbefa4fa4 ;
}

void
sha384_engine::process_block( state_type & state, block_type const & block )
{
    return sha512_engine::process_block( state, block ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
