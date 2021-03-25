// ===========================================================================
//                        Copyright 2013 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Interface to the CPUID instruction available on x86 and
//!            x86_64 architectures.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_NdxCdLqwZx3xIY8HOQTuNFqrCGUmVJGH
#define BREEZE_GUARD_NdxCdLqwZx3xIY8HOQTuNFqrCGUmVJGH

#include "breeze/top_level_namespace.hpp"
#include <cstdint>

namespace breeze_ns {

//      cpuid_result:
//      =============
//
//!     \brief
//!         The result of the CPUID instruction.
// ---------------------------------------------------------------------------
struct cpuid_result
{
    std::uint32_t       eax ;
    std::uint32_t       ebx ;
    std::uint32_t       ecx ;
    std::uint32_t       edx ;
} ;

//      get_cpuid_info():
//      =================
//
//!     \brief
//!         Executes the CPUID instruction with the provided values in
//!         `EAX` and `ECX`.
//!
//!     \pre
//!         The CPUID instruction is supported (this is always true on
//!         x86_64 CPUs).
//!
//!     \return
//!         A struct with the values of `EAX`, `EBX`, `ECX`, `EDX`
//!         returned by the CPUID instruction itself.
//!
//!     \note
//!         Note that all the values (either in input and output) are
//!         32-bit. This is not by mistake: the CPUID instruction still
//!         uses 32-bit values even in 64-bit mode.
//!     \note
//!         It's intended that this function is the lowest level before
//!         dealing with assembly. And that higher level interfaces be
//!         defined upper in the library/application logic.
// ---------------------------------------------------------------------------
cpuid_result        get_cpuid_info( std::uint32_t eax, std::uint32_t ecx ) ;

}

#endif
