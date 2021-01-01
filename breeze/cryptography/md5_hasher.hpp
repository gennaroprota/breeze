// ===========================================================================
//                     Copyright 2006-2007 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief MD5 policy and typedef's for MD5 hasher and digest.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_vePXQ5mxXBYih5DCVW1zUWqL52bOdtiX
#define BREEZE_GUARD_vePXQ5mxXBYih5DCVW1zUWqL52bOdtiX

#include "breeze/top_level_namespace.hpp"
#include "breeze/cryptography/merkle_damgard_engine.hpp"
#include "breeze/cryptography/merkle_damgard_machine.hpp"

namespace breeze_ns {

class md5_engine ;

template< typename Hasher >
class digest ;

//!\{
//!     Convenience typedef(s).
// ---------------------------------------------------------------------------
typedef merkle_damgard_machine< md5_engine > md5_hasher ;
typedef digest< md5_hasher >                 md5_digest ;
//!\}


//!     The MD5 policy class for \c merkle_damgard_machine.
// ---------------------------------------------------------------------------
class md5_engine
    :   public merkle_damgard_engine< 128, 512, little_endian_policy,
                                       32, 128, hashing_count::wraps >
{
public:
    static void         init_state( state_type & state ) ;

    static void         process_block( state_type & state,
                                       block_type const & block ) ;
} ;

}

#endif
