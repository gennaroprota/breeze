// =========================================================================
//                       Copyright 2016 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief  SHA-384 function.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_K9MoyAqzzHMnugSwsAjPtZppm3h4NXaI
#define BREATH_GUARD_K9MoyAqzzHMnugSwsAjPtZppm3h4NXaI

#include "breath/cryptography/merkle_damgard_engine.hpp"
#include "breath/cryptography/merkle_damgard_machine.hpp"

namespace breath {

class               sha384_engine ;

template< typename Hasher >
class               digest ;

typedef merkle_damgard_machine< sha384_engine >
                    sha384_hasher ;
typedef digest< sha384_hasher >
                    sha384_digest ;

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

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:

