# ============================================================================
#                      Copyright 2013-2018 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________

#       Maintenance note:
#       -----------------
#
#       Be sure that modifications to these options don't put the various
#       compiler-specific makefiles out of sync (e.g. by requiring
#       C++14 with one compiler and C++17 with another).
#
#
#       As usual, the options are listed in two groups. The group
#       appearing first relates mainly to standards conformance. The
#       other group contains other options in alphabetical order.
#
#       Special notes for some of the options:
#       ======================================
#
#       (See gcc.mk for further notes on some options.)
#
#       -Wno-weak-vtables:
#
#           The -Wweak-vtables warning tries to point out possible
#           object files bloat, but that's probably moot either because
#           it isn't really going to make a difference on performances,
#           and because the linker will likely collapse the duplicated
#           vtables anyway.
#
#           So this warning can be safely suppressed. Note, too, that
#           it would be difficult to silence it by modifying the code,
#           as in the case (as of Febrary 27, 2009) for the class
#           command_line_error, in command_line.hpp.
# ----------------------------------------------------------------------------

#       KEEP in sync! (See above.)
# ----------------------------------------------------------------------------
cpp_basic_options =  -std=c++14                 \
                     -Weverything               \
                     -Wno-c++98-compat          \
                     -Wno-c++98-compat-pedantic \
                     -Werror                    \
                     -fuse-cxa-atexit           \
                     -D _POSIX_C_SOURCE=200112L \
                     -U _GNU_SOURCE             \
                     -D _GLIBCXX_USE_CXX11_ABI=1

cpp_basic_options += -pipe                      \
                     -Wno-padded                \
                     -Wno-weak-vtables

#       The following three options are temporary (the -Wno-documentation...
#       is because Clang doesn't seem to recognize the \cond command)- gps
# ----------------------------------------------------------------------------
cpp_basic_options += -Wno-exit-time-destructors \
                     -Wno-global-constructors   \
                     -Wno-documentation-unknown-command

#       See:
#       <https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_macros.html>.
#
#       Keep in sync with gcc.mk.
# ----------------------------------------------------------------------------
cpp_debug_options =  -D _GLIBCXX_ASSERTIONS=1        \
                     -D _GLIBCXX_CONCEPT_CHECKS      \
                     -D _GLIBCXX_DEBUG               \
                     -D _GLIBCXX_DEBUG_PEDANTIC

cpp_debug_options += -ggdb3


include_switch = -I
object_file_suffix = .o

#       Note that this differs from the compiler name, which is in
#       $(compiler).
# ----------------------------------------------------------------------------
compiler_command = clang++

define compile_to_object
    $(compiler_command) $(cpp_options) -c -o $@ $<
endef

define link_to_exec
    $(compiler_command) $(cpp_options) -o $@ $+
endef


# Local Variables:
# mode: makefile
# indent-tabs-mode: nil
# End:
# vim: set ft=make et sts=4 sw=4:
