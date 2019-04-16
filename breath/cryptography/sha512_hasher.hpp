// ===========================================================================
//                     Copyright 2006-2007 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief SHA-512 function.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_wCcpHSPgQuuMlLcoiraq0109Dj5dIMnV
#define BREATH_GUARD_wCcpHSPgQuuMlLcoiraq0109Dj5dIMnV

#include "breath/cryptography/merkle_damgard_engine.hpp"
#include "breath/cryptography/merkle_damgard_machine.hpp"

namespace breath {

class               sha512_engine ;

template< typename Hasher >
class               digest ;

//!     Convenience typedefs
// ---------------------------------------------------------------------------
typedef merkle_damgard_machine< sha512_engine >
                    sha512_hasher ;
typedef digest< sha512_hasher >
                    sha512_digest ;

//      sha512_engine:
//      ==============
//
//!     SHA-512 policy class for merkle_damgard_machine.
// ---------------------------------------------------------------------------
class sha512_engine
    :   public merkle_damgard_engine< 512, 1024, big_endian_policy, 64 >
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
