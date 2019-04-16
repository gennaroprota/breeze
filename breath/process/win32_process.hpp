// ===========================================================================
//                        Copyright 2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Represents a Win32 process.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_R609ymqmTeLeF2v3mTEcOyW8AqCEibGg
#define BREATH_GUARD_R609ymqmTeLeF2v3mTEcOyW8AqCEibGg

#include "breath/idiom/declare_non_copyable.hpp"
#include "breath/process/process.hpp"
#include <cstddef>
#include <string>

namespace breath {

//      win32_process:
//      ==============
//
//!     A Win32 process. Provides operations which aren't available in
//!     the portable process class.
// ---------------------------------------------------------------------------
class win32_process
    :   public process
{
public:
    BREATH_DECLARE_NON_COPYABLE( win32_process )

     //                   win32_process( process_id_type id ) ;
    std::string         name() const ;
    std::size_t         module_count() const ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
