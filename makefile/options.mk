# ============================================================================
#                         Copyright 2021 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________

cpp_options := $(cpp_basic_options)

ifeq ($(build_type),optimized)
    cpp_options += $(cpp_optimize_options)
else
    cpp_options += $(cpp_debug_options)
endif

cpp_preprocessing_defines += -D BREEZE_SYSTEM_FAMILY=$(system_family)   \
                             -D BREEZE_SYSTEM=$(system)                 \
                             -D BREEZE_COMPILER=$(compiler)

cpp_options += $(cpp_extra_options)                 \
               $(include_switch)"$(include_dir)"    \
               $(cpp_preprocessing_defines)
