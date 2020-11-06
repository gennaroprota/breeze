# ============================================================================
#                         Copyright 2016 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________

root         := ../..

source_files := include_guard.cpp               \
                macro_name.cpp

ifeq ($(system),windows)
    libraries += Advapi32
endif

include $(root)/makefile/executable.mk

# Local Variables:
# mode: makefile
# indent-tabs-mode: nil
# End:
# vim: set ft=make et sts=4 sw=4:
