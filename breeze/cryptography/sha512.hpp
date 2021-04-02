// ===========================================================================
//                     Copyright 2006-2007 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief SHA-512, SHA-512/224 and SHA-512/256 policies, and
//!            typedefs for the corresponding hashers and digests.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_wCcpHSPgQuuMlLcoiraq0109Dj5dIMnV
#define BREEZE_GUARD_wCcpHSPgQuuMlLcoiraq0109Dj5dIMnV

#include "breeze/top_level_namespace.hpp"
#include "breeze/cryptography/digest.hpp"
#include "breeze/cryptography/merkle_damgard_engine.hpp"
#include "breeze/cryptography/merkle_damgard_machine.hpp"

namespace breeze_ns {

class               sha512_engine     ;
class               sha512_224_engine ;
class               sha512_256_engine ;

//!\{
//!     A convenience typedef.
// ---------------------------------------------------------------------------
typedef merkle_damgard_machine< sha512_engine >
                    sha512_hasher ;
typedef digest< sha512_hasher >
                    sha512_digest ;

typedef merkle_damgard_machine< sha512_224_engine >
                    sha512_224_hasher ;
typedef digest< sha512_224_hasher >
                    sha512_224_digest ;

typedef merkle_damgard_machine< sha512_256_engine >
                    sha512_256_hasher ;
typedef digest< sha512_256_hasher >
                    sha512_256_digest ;

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

//      sha512_224_engine:
//      ==================
//
//!     SHA-512/224 policy class for `merkle_damgard_machine`. This
//!     corresponds to SHA-512/224 as described in FIPS 180-4.
// ---------------------------------------------------------------------------
class sha512_224_engine
    :   public merkle_damgard_engine< 224, 1024, big_endian_policy, 64, 512 >
{
public:
    static void         init_state( state_type & state ) ;
    static void         process_block( block_type const & block,
                                       state_type & state ) ;
} ;

//      sha512_256_engine:
//      ==================
//
//!     SHA-512/256 policy class for `merkle_damgard_machine`. This
//!     corresponds to SHA-512/256 as described in FIPS 180-4.
// ---------------------------------------------------------------------------
class sha512_256_engine
    :   public merkle_damgard_engine< 256, 1024, big_endian_policy, 64, 512 >
{
public:
    static void         init_state( state_type & state ) ;
    static void         process_block( block_type const & block,
                                       state_type & state ) ;
} ;

}

#endif
