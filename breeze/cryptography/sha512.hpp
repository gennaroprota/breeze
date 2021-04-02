// ===========================================================================
//                     Copyright 2006-2007 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief SHA-512 policy and typedefs for SHA-512 hasher and
//!            digest.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_wCcpHSPgQuuMlLcoiraq0109Dj5dIMnV
#define BREEZE_GUARD_wCcpHSPgQuuMlLcoiraq0109Dj5dIMnV

#include "breeze/top_level_namespace.hpp"
#include "breeze/cryptography/digest.hpp"
#include "breeze/cryptography/merkle_damgard_engine.hpp"
#include "breeze/cryptography/merkle_damgard_machine.hpp"

namespace breeze_ns {

class               sha512_engine ;

//!\{
//!     A convenience typedef.
// ---------------------------------------------------------------------------
typedef merkle_damgard_machine< sha512_engine >
                    sha512_hasher ;
typedef digest< sha512_hasher >
                    sha512_digest ;
//!\}

//      sha512_engine:
//      ==============
//
//!     SHA-512 policy class for `merkle_damgard_machine`. This
//!     corresponds to SHA-512 as described in FIPS 180-2 with Change
//!     Notice 1.
// ---------------------------------------------------------------------------
class sha512_engine
    :   public merkle_damgard_engine< 512, 1024, big_endian_policy, 64 >
{
public:
    static void         init_state( state_type & state ) ;
    static void         process_block( block_type const & block,
                                       state_type & state ) ;
} ;

}

#endif
