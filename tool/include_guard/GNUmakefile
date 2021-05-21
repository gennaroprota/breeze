# ============================================================================
#                         Copyright 2016 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________

root                    := ../..

source_files            := include_guard.cpp               \
                           macro_name.cpp

libraries               := breeze
ifeq ($(system),windows)
    additional_libraries+= Advapi32
endif

exe_base_name           := include_guard
include $(root)/makefile/executable.mk
