# ============================================================================
#                      Copyright 2013-2019 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________


.intel_syntax noprefix

.global             get_cpuid_info

.text

get_cpuid_info:

    mov r10, r8
    mov  r8, rcx
    mov  r9, rdx

    push rbx
    push rcx
    push rdx

    mov eax, r9d
    mov ecx, r10d

    cpuid

    mov dword ptr [ r8      ], eax
    mov dword ptr [ r8 + 4  ], ebx
    mov dword ptr [ r8 + 8  ], ecx
    mov dword ptr [ r8 + 12 ], edx

    mov rax, r8            /* the ABI requires the struct address in RAX */

    pop rdx
    pop rcx
    pop rbx
    ret

# Local Variables:
# mode: asm
# End:
# vim: set ft=asm et sts=4 sw=4:
