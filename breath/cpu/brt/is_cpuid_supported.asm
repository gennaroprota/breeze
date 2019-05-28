# ============================================================================
#                         Copyright 2013 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________

.intel_syntax noprefix

.global             _is_cpuid_supported

.text

/*
;       is_cpuid_supported():
;       =====================
;
;       A simple routine to correctly detect the presence of the CPUID
;       machine instruction.
;
;       Assumes:
;
;         - 32-bit processor or later (so it is safe to use the pushfd
;           instruction)
;         - the "ID flag" is available (486 or later)
;         - the CPU is Intel?
;
;       Note that in 64-bit executables you don't need this routine at
;       all, at least if the CPU is Intel, since all 64-bit Intel's do
;       support CPUID. (This is a welcome thing, because, of course, it
;       spares us from maintaining a slightly different version for
;       x86-64.)
;
;       [TODO: what about Virtual Machines?]
;
;       References:
;       -----------
;
;       1) Intel® 64 and IA-32 Architectures
;          Software Developer's Manual
;          Volume 2 (2A, 2B & 2C):
;          Instruction Set Reference, A-Z
;
;          Order Number: 325383-047US
;          June 2013
;
;       2) Intel® Processor Identification and the CPUID Instruction
;          Application Note 485
;          July 2004
;          Document Number: 241618-027
;
;          (This covers things up to the original 8086. Of course we can
;          assume much newer CPUs and simplify the code a lot. But if
;          you need to expand this to support e.g. a 386, it can tell
;          you how.)
;
;       Strategy:
;       ---------
;
;       The technique used here is from [1]:
;
;       "The ID flag (bit 21) in the EFLAGS register indicates support
;       for the CPUID instruction. If a software procedure can set and
;       clear this flag, the processor executing the procedure supports
;       the CPUID instruction."
;
;       (Note that according to [2] you can't rely on the absence of an
;       invalid opcode trap, instead.)
;
;       Special note:
;
;           the quote above from the Intel manual talks about setting
;           *and* clearing. It is not clear whether one should really
;           verify both (and, in that case, whether they should be
;           verified in order), or if one implies the other. The
;           application note just considers *modifying* (flipping), and
;           so do all the code snippets I've seen from Intel. I'm
;           assuming, therefore, that this is enough.
; ----------------------------------------------------------------------------
;
;       C interface:    int is_cpuid_supported() ;
;
;       Returns 1 if and only if the CPU that executes it supports the
;       CPUID instruction. Otherwise 0.
;
;           [gps a processor executes the whole function?]
; ----------------------------------------------------------------------------
*/

_is_cpuid_supported:

.equ id_bit_pos, 21

    /* push ECX ?? gps */

    /* get EFLAGS in EAX and save a copy in ECX   */
    /* for later testing (and restoring)          */
    pushfd
    pop eax
    mov ecx, eax

    /* attempt to replace the value in EFLAGS     */
    xor eax, ( 1 << id_bit_pos )
    push eax
    popfd

    /* get the (new) value of EFLAGS              */
    pushfd
    pop eax

    /* store in EAX (return value) a "compare" of */
    /* old and new value of the ID bit            */
    xor eax, ecx
    shr eax, id_bit_pos
    and eax, 1

    /* restore EFLAGS                             */
    push ecx
    popfd
    ret

# Local Variables:
# mode: asm
# End:
# vim: set ft=asm et sts=4 sw=4:
