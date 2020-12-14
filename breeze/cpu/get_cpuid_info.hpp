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

#include <cstdint>

extern "C" {

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
//!         \c EAX and \c ECX.
//!
//!     Namespace: global (see below).
//!
//!     \pre
//!         The CPUID instruction is supported (this is always true on
//!         x86_64 CPUs).
//!
//!     \return
//!         A struct with the values of \c EAX, \c EBX, \c ECX, \c EDX
//!         returned by the CPUID instruction itself.
//!
//!     \note
//!         Unusually for our code base, this file uses <code>extern "C"
//!         </code>; that's because the actual routines are written in
//!         assembly and it is just easier to write portable assembly
//!         that way (no name mangling differences, for example). The
//!         fact that the routines are written in assembly however is an
//!         implementation detail (which I'm mentioning just to provide
//!         the rationale for <code>extern "C"</code>).
//!     \note
//!         Once you use <code>extern "C"</code>, then, you're better
//!         off not using a namespace (because it would be ignored by
//!         the linker anyway). So, the names here are *global*.
//!     \note
//!         Finally, note that all the values (either in input and
//!         output) are 32-bit. This is not by mistake: the CPUID
//!         instruction still uses 32-bit values even in 64-bit mode.
//!     \note
//!         It's intended that these functions are the lowest level
//!         before dealing with assembly. And that higher level
//!         interfaces be defined upper in the library/application
//!         logic.
// ---------------------------------------------------------------------------
cpuid_result        get_cpuid_info( std::uint32_t eax, std::uint32_t ecx ) ;

}

#endif