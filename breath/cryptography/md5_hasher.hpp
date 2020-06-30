// ===========================================================================
//                     Copyright 2006-2007 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief MD5 templates.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_vePXQ5mxXBYih5DCVW1zUWqL52bOdtiX
#define BREATH_GUARD_vePXQ5mxXBYih5DCVW1zUWqL52bOdtiX

#include "breath/top_level_namespace.hpp"
#include "breath/cryptography/merkle_damgard_engine.hpp"
#include "breath/cryptography/merkle_damgard_machine.hpp"

namespace breath_ns {

class md5_engine ;

template< typename Hasher >
class digest ;

//
//      Convenience typedef(s)
// ---------------------------------------------------------------------------
typedef merkle_damgard_machine< md5_engine > md5_hasher ;
typedef digest< md5_hasher >                 md5_digest ;


//!     The MD5 policy class for merkle_damgard_machine.
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

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
