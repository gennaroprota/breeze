// ===========================================================================
//                        Copyright 2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Represents a child process in the system.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_xHOnLsh9W9NZSotPhf95oOS1ufiT1xmH
#define BREATH_GUARD_xHOnLsh9W9NZSotPhf95oOS1ufiT1xmH

#include "breath/idiom/declare_non_copyable.hpp"
#include "breath/process/process.hpp"

namespace breath {

class child_process
    :   public process
{
public:
    BREATH_DECLARE_NON_COPYABLE( child_process )

                        child_process() ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
