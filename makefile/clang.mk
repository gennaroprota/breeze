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
#       Be sure that modifications to these options don't put the
#       various compiler-specific makefiles out of sync (e.g. by
#       requiring C++14 with one compiler and C++17 with another).
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
#           So this warning can be safely suppressed. Note, too, that it
#           would be difficult to silence it by modifying the code, as
#           in the case (as of Febrary 27, 2019) for the class
#           command_line_error, in command_line.hpp.
#
#       -Wno-zero-as-null-pointer-constant
#
#           Silences warnings on things like:
#
#             if ( GetModuleHandle( L"kernel32" ) == NULL )
#                 ...
#
#           (we don't want to use nullptr, there). GCC seems to be
#           smarter and doesn't give such warnings when the option is
#           enabled.
# ----------------------------------------------------------------------------

#       KEEP in sync! (See above.)
# ----------------------------------------------------------------------------
cpp_basic_options := -std=c++14                         \
                     -Weverything                       \
                     -Wno-c++98-compat                  \
                     -Wno-c++98-compat-pedantic         \
                     -Werror                            \
                     -fuse-cxa-atexit                   \
                     -D _POSIX_C_SOURCE=200809L         \
                     -D _GLIBCXX_USE_CXX11_ABI=1

cpp_basic_options += -pipe                              \
                     -Wno-padded                        \
                     -Wno-sign-conversion               \
                     -Wno-weak-vtables                  \
                     -Wno-zero-as-null-pointer-constant

#       The following three options are temporary
#       (-fcomment-block-commands=cond is a hack for Clang, which
#       doesn't seem to recognize the \cond command, although it
#       recognizes \endcond; this is better than using
#       -Wno-documentation-unknown-command, as that could hide real
#       errors). - gps
# ----------------------------------------------------------------------------
cpp_basic_options += -Wno-exit-time-destructors         \
                     -Wno-global-constructors           \
                     -fcomment-block-commands=cond

#       See:
#       <https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_macros.html>.
#
#       Keep in sync with gcc.mk.
# ----------------------------------------------------------------------------
cpp_debug_options := -D _GLIBCXX_ASSERTIONS=1           \
                     -D _GLIBCXX_CONCEPT_CHECKS         \
                     -D _GLIBCXX_DEBUG                  \
                     -D _GLIBCXX_DEBUG_PEDANTIC

cpp_debug_options += -ggdb3


include_switch := -I
object_file_suffix := .o

#       Note that this differs from the compiler name, which is in
#       $(compiler). And that, for Travis CI, we often need to select a
#       specific version (e.g. clang++-8), which we do externally to
#       this makefile: hence the ifndef test.
# ----------------------------------------------------------------------------
ifndef compiler_command
    compiler_command := clang++
endif

compiler_display_name := Clang

#       Get the version number from --version, because Clang's
#       -dumpversion lies, for GCC compatibility.
# ----------------------------------------------------------------------------
compiler_version := $(shell $(compiler_command) --version 2>&1 |    \
                 sed -n 's/.*version \([1-9]\+[0-9]*\.[0-9]*\.[0-9]*\).*/\1/p' )

define compile_to_object
    $(compiler_command) $(cpp_options) -c -o $@ $<
endef

define compile_to_dependency
    $(compiler_command) $(cpp_options) -MT $@ -M -MP            \
                        -MF $(dependency_dir)/$*.temp_dep $<
endef

define build_library
    rm -f $@
    ar -rc $@ $^
endef

define link_to_exec
    $(compiler_command) $(cpp_options) -o $@ $+
endef

# Local Variables:
# mode: makefile
# indent-tabs-mode: nil
# End:
# vim: set ft=make et sts=4 sw=4:
