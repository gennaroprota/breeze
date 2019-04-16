# ============================================================================
#                         Copyright 2013 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________


.intel_syntax noprefix

.global             _get_cpuid_info

.text

_get_cpuid_info:

    push ebp
    mov ebp, esp

    push ebx
    push esi                /* save this, which we use for temp storage */

    mov esi, [ ebp + 8  ]
    mov eax, [ ebp + 12 ]
    mov ecx, [ ebp + 16 ]

    cpuid

    mov [ esi ],     eax
    mov [ esi + 4  ], ebx
    mov [ esi + 8  ], ecx
    mov [ esi + 12 ], edx

    mov eax, esi            /* the ABI requires the struct address in EAX */

    pop esi
    pop ebx

    pop ebp
    ret

# Local Variables:
# mode: asm
# End:
# vim: set ft=asm et sts=4 sw=4:
