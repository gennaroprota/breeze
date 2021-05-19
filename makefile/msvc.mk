# ============================================================================
#                      Copyright 2008-2019 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________
#
#       Maintenance note:
#       -----------------
#
#       Be sure that modifications to these options don't put the
#       various compiler-specific makefiles out of sync (e.g. by
#       requiring C++14 with one compiler and C++17 with another).
#
#
#       As usual, the options are listed in two groups. The group
#       appearing first relates mainly to standards conformance.
#
#       Rationale
#       =========
#
#       /Za [not used]:
#
#           ideally I'd use this option everywhere, except for the
#           translation units including <Windows.h> (or other Windows
#           headers that need the Microsoft extensions).
#
#           BUT: can we assume that object files generated with /Za can
#           link with others that do not, without causing any undefined
#           behavior?  Even if /Za vs. /Ze was the only variation (i.e.
#           if *all* the other options were kept the same) I don't think
#           we can be sure. Thus I give up using /Za, for any source
#           file.
#
#       /Zc:referenceBinding [not used]:
#
#           this disables binding rvalues to references to non-const.
#           It's not really necessary: VC++ emits a warning at /W4 and
#           higher and we don't admit warnings (and mutate them into
#           errors).
#
#       /Zc:rvalueCast and /Zc:strictStrings:
#
#           these were used with MSVC 2015; now that we require at least
#           MSVC 2017, they are implied by permissive-, but we left them
#           in case someone wants to backport the library to MSVC 2015.
#
#       /volatile:iso
#
#           it seems (but I've not verified) that this is not implied by
#           /std:xx, so I add it explicitly, to avoid accidentally
#           relying on behavior not guaranteed by the C++ standard.
#
#       /analyze [not used]:
#
#           I'd love to use it, but it's giving the following apparently
#           bogus error:
#
#           c:\program files (x86)\windows kits\10\include\10.0.17134.0\um\winioctl.h(4600) :
#           warning C6001: Using uninitialized memory '*Input'.: Lines: 4584, 4591, 4592, 4593, 4594, 4596, 4600
#
#           NOTE: the error doesn't appear when running the analyzer
#                 from the Visual Studio 2015 IDE, so I've added the
#                 switch in the Visual Studio project (the project is
#                 temporary and might have disappeared when you'll read
#                 this).
# ----------------------------------------------------------------------------


#       Needed, otherwise we'll get Windows' sort, below.
# ----------------------------------------------------------------------------
cygwin_sort := '/bin/sort'

minimum_msvc_version := 19.15.26726

compiler_display_name := MSVC

compiler_version := $(shell cl 2>&1 | head -1 | grep -E -o \
                                "[1-9][0-9]*\.[0-9]+\.[0-9]+\.?[0-9]*")

lowest_version := $(shell                                                \
  printf '%s\n%s\n' $(minimum_msvc_version) $(compiler_version)  |       \
  $(cygwin_sort) -t . -k 1,1n -k 2,2n -k 3,3n -k 4,4n | head -1          \
  )

ifneq "$(lowest_version)" "$(minimum_msvc_version)"
    $(error You are using Visual C++ $(compiler_version) but the minimum \
            supported version is $(minimum_msvc_version))
endif


#       KEEP in sync! (See above.)
# ----------------------------------------------------------------------------
cpp_basic_options := /std:c++14                 \
                     /Zc:forScope               \
                     /Zc:wchar_t                \
                     /Zc:auto                   \
                     /Zc:trigraphs              \
                     /Zc:rvalueCast             \
                     /Zc:strictStrings          \
                     /Zc:inline                 \
                     /volatile:iso              \
                                                \
                     /EHs                       \
                     /Wall                      \
                     /WX                        \
                     /D _CRT_SECURE_NO_WARNINGS \
                     /D _SCL_SECURE_NO_WARNINGS

cpp_basic_options += /nologo

cpp_basic_options += /wd4068        # unknown pragma (see gcc.mk for the why)

#       Enable /Wall, except for a handful of warnings (some of which
#       arise in the standard headers). For a synopsis, see:
#
#         <https://docs.microsoft.com/en-us/cpp/preprocessor/compiler-warnings-that-are-off-by-default?view=vs-2015>
# ----------------------------------------------------------------------------
cpp_basic_options += /wd4191 /wd4365 /wd4514 /wd4571    \
                     /wd4668 /wd4710 /wd4820

#       Starting with Visual C++ 2017, disable these, most of which
#       arise in standard headers. But enable /permissive-.
# ----------------------------------------------------------------------------
cpp_basic_options += /wd4623 /wd4625 /wd4626 /wd4774        \
                     /wd5026 /wd5027 /wd5045 /permissive-

#       These were encountered with MSVC 2019, when including
#       <Windows.h>, and are related to messing up with #pragma pop/
#       #pragma push. But why don't they occur when using the IDE?
# ----------------------------------------------------------------------------
cpp_basic_options += /wd5031 /wd5032

#       Apparently, MSVC 2019 emits more of these than MSVC 2017, so,
#       rather than littering our code with calls to as_non_constant(),
#       we just disable the warning.
# ----------------------------------------------------------------------------
cpp_basic_options += /wd4127

#       This is about shifting an integer by a too large amount;
#       unfortunately, it is also emitted if the offending code is
#       guarded by an if statement which makes the "excessive" shift
#       impossible. We still check for such shifts with GCC and Clang
#       (which don't have the just mentioned problem), so disabling the
#       warning with MSVC is OK.
# ----------------------------------------------------------------------------
cpp_basic_options += /wd4333

cpp_optimize_options = /O2 /Oi /GL /wd4711

include_switch := /I
object_file_suffix := .obj

additional_library_options := $(addsuffix $(library_name_suffix),   \
                     $(addprefix $(library_name_prefix),$(additional_libraries)))

compiler_command := cl

linker_options := /WX /LTCG

define compile_to_object
    $(compiler_command) $(cpp_options) /c /Fo$@ $<
endef

#       Note: the two final sed substitutions escape the drive separator
#       (colon) and the spaces in the path (excluding the space right
#       before the path itself, which can be easily recognized because
#       it's preceded by a colon).
# ----------------------------------------------------------------------------
define compile_to_dependency
    $(compiler_command) $(cpp_options) /E $<                        |   \
        sed -n 's|^\#line *[0-9][0-9]* *"\([^"]*\)".*|$@: \1|p'     |   \
        sed -e 's|\:\\|\\:\\|'                                          \
            -e 's|\([^:]\) |\1\\ |g'                                |   \
        $(cygwin_sort) -u > $(dependency_dir)/$*.temp_dep
endef

define build_library
    rm -f $@
    lib /OUT:$@ /WX $^
endef

#       Note that the /link option (and its arguments) must appear last.
#
#       We need to invoke the linker, not the compiler; but using cl.exe
#       is handy because it automatically translates some of the options
#       that we have in the variable $(cpp_options): e.g. /Zd -> /DEBUG.
#       If we invoked link.exe directly, we'd need to setup another
#       variable, for the linker, with options in sync with the compiler
#       ones. [gps]
# ----------------------------------------------------------------------------
define link_to_exec
    $(compiler_command) $(cpp_options) /Fe$@  $+                \
                        /link $(linker_options) $(additional_library_options)
endef
