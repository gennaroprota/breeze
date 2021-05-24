# ============================================================================
#                         Copyright 2019 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________


library_name_prefix     :=
library_name_suffix     := .lib
exe_name_suffix         := .exe

system_family           := windows

#       This was introduced to get the declaration of GetProductInfo()
#       with GCC under Cygwin.
# ----------------------------------------------------------------------------
cpp_preprocessing_defines \
                        += -D _WIN32_WINNT=0x600
