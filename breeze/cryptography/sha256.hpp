// ===========================================================================
//                     Copyright 2006-2007 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief  SHA-256 policy and typedef's for SHA-256 hasher and
//!             digest.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_t9rt82w9uC5ZSdNs25Tb0en1bhYQjfnf
#define BREEZE_GUARD_t9rt82w9uC5ZSdNs25Tb0en1bhYQjfnf

#include "breeze/top_level_namespace.hpp"
#include "breeze/cryptography/digest.hpp"
#include "breeze/cryptography/merkle_damgard_engine.hpp"
#include "breeze/cryptography/merkle_damgard_machine.hpp"

namespace breeze_ns {

class               sha256_engine ;

//!\{
//!     A convenience typedef.
// ---------------------------------------------------------------------------
typedef merkle_damgard_machine< sha256_engine >
                    sha256_hasher ;
typedef digest< sha256_hasher >
                    sha256_digest ;
//!\}

//      sha256_engine:
//      ==============
//
//!     SHA-256 policy class for \c merkle_damgard_machine.
// ---------------------------------------------------------------------------
class sha256_engine
    :   public merkle_damgard_engine< 256, 512, big_endian_policy >
{
public:
    static void         init_state( state_type & state ) ;
    static void         process_block( state_type & state,
                                       block_type const & block ) ;
} ;

}

#endif
