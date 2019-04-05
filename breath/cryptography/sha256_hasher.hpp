// =========================================================================
//                    Copyright 2006-2007 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief  SHA-256 function.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_t9rt82w9uC5ZSdNs25Tb0en1bhYQjfnf
#define BREATH_GUARD_t9rt82w9uC5ZSdNs25Tb0en1bhYQjfnf

#include "breath/cryptography/merkle_damgard_engine.hpp"
#include "breath/cryptography/merkle_damgard_machine.hpp"

namespace breath {

class               sha256_engine ;

template< typename Hasher >
class               digest ;


//!     Convenience typedefs
// -------------------------------------------------------------------------
typedef merkle_damgard_machine< sha256_engine >
                    sha256_hasher ;
typedef digest< sha256_hasher >
                    sha256_digest ;

//      sha256_engine:
//      ==============
//
//!     SHA-256 policy class for merkle_damgard_machine.
// -------------------------------------------------------------------------
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

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
