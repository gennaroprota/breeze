// ===========================================================================
//                     Copyright 2006-2007 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief  SHA-224 policy and typedef's for SHA-224 hasher and
//!             digest.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_OKBGme15I2KXAgAlHJL4gxgCmNkNyA1w
#define BREEZE_GUARD_OKBGme15I2KXAgAlHJL4gxgCmNkNyA1w

#include "breeze/top_level_namespace.hpp"
#include "breeze/cryptography/digest.hpp"
#include "breeze/cryptography/merkle_damgard_engine.hpp"
#include "breeze/cryptography/merkle_damgard_machine.hpp"

namespace breeze_ns {

class               sha224_engine ;

typedef merkle_damgard_machine< sha224_engine >
                    sha224_hasher ;
typedef digest< sha224_hasher >
                    sha224_digest ;

//      sha224_engine:
//      ==============
//
//!     SHA-224 policy class for \c merkle_damgard_machine.
// ---------------------------------------------------------------------------
class sha224_engine
    :   public merkle_damgard_engine< 224, 512, big_endian_policy, 32, 256 >
{
public:
    static void         init_state( state_type & state ) ;
    static void         process_block( state_type & state,
                                       block_type const & block ) ;
} ;

}

#endif
