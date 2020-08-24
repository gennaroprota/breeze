// ===========================================================================
//                        Copyright 2013 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Interface to the CPUID instruction.
// ---------------------------------------------------------------------------
//
//!     Interface to the CPUID instruction available on x86 and x86_64
//!     architectures.
//!
//!     NOTE: unusually for our code base, this file uses extern "C";
//!     that's because the actual routines are written in assembly and
//!     it is just easier to write portable assembly that way (no name
//!     mangling differences, for example). The fact that the routines
//!     are written in assembly however is an implementation detail
//!     (which I'm mentioning just to provide the rationale for extern
//!     "C").
//!
//!     Once you use extern "C", then, you're better off not using a
//!     namespace (because it would be ignored by the linker anyway).
//!     So, the names here are *global*.
//!
//!     Finally, note that all the values (either in input and output)
//!     are 32-bit. This is not by mistake: the CPUID instruction still
//!     uses 32-bit values even in 64-bit mode.
//!
//!     It's intended that these functions are the lowest level before
//!     dealing with assembly. And that higher level interfaces be
//!     defined upper in the library/application logic.
// ---------------------------------------------------------------------------

#include <cstdint>

extern "C" {

//!     Represents the result of the CPUID instruction.
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
//!     Namespace: global (see above).
//!
//!     Executes the CPUID instruction with the provided values in \c
//!     EAX and \c ECX.
//!
//!     \pre
//!         The CPUID instruction is supported (this is always true on
//!         x86_64 CPUs).
//!
//!     \return
//!         A struct with the values of \c EAX, \c EBX, \c ECX, \c EDX
//!         returned by the CPUID instruction itself.
// ---------------------------------------------------------------------------
cpuid_result        get_cpuid_info( std::uint32_t eax, std::uint32_t ecx ) ;

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
