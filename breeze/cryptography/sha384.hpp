// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief  SHA-384 policy and typedefs for SHA-384 policy and
//!             digest.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_K9MoyAqzzHMnugSwsAjPtZppm3h4NXaI
#define BREEZE_GUARD_K9MoyAqzzHMnugSwsAjPtZppm3h4NXaI

#include "breeze/top_level_namespace.hpp"
#include "breeze/cryptography/digest.hpp"
#include "breeze/cryptography/merkle_damgard_engine.hpp"
#include "breeze/cryptography/merkle_damgard_machine.hpp"

namespace breeze_ns {

class               sha384_engine ;

//!\{
//!     A convenience typedef.
// ---------------------------------------------------------------------------
typedef merkle_damgard_machine< sha384_engine >
                    sha384_hasher ;
typedef digest< sha384_hasher >
                    sha384_digest ;
//!\}

//      sha384_engine:
//      ==============
//
//!     SHA-384 policy class for `merkle_damgard_machine`.
// ---------------------------------------------------------------------------
class sha384_engine
    :   public merkle_damgard_engine< 384, 1024, big_endian_policy, 64, 512 >
{
public:
    static void         init_state( state_type & state ) ;
    static void         process_block( state_type & state,
                                       block_type const & block ) ;
} ;

}

#endif
