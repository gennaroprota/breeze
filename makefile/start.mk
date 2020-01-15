# ============================================================================
#                      Copyright 2006-2020 Gennaro Prota
#                         Copyright 2000 James Kanze
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________


# This file assumes the following variables are defined:

#  - compiler
#  - subdirs?? -gps


#       Rationale:
#
#       this is almost always what one wants; see:
#
#         <https://www.gnu.org/software/make/manual/html_node/Errors.html>.
# ----------------------------------------------------------------------------
.DELETE_ON_ERROR:


.SHELLFLAGS += -e -u
MAKEFLAGS += --warn-undefined-variables

ifeq ($(and $(compiler), $(system)),)
    $(error Please, define 'compiler' and 'system' on the command line; e.g. \
            run 'compiler=gcc system=unix make')
endif


default_architecture := x86_64

ifndef architecture
    architecture := $(default_architecture)
endif

ifeq ($(architecture),)
    architecture := $(default_architecture)
endif

#       Recurses on the same target. $(subdirs) must be defined before
#       including this file for it to work.
#
#       Function originally taken from James Kanze's GABI Library
#       version 2005v01 (named "doForAll", there).
# ----------------------------------------------------------------------------
define do_for_all_subdirs
    for x in $(subdirs) ;               \
    do                                  \
        $(MAKE) -C $$x $@ || exit $$? ; \
    done
endef

define build_library
    rm -f $@
    ar -rc $@ $^
endef


include_dir     := $(root)

cpp_options = $(cpp_basic_options)                  \
              $(cpp_debug_options)                  \
              $(cpp_extra_options)                  \
              $(include_switch)"$(include_dir)"     \
              $(cpp_preprocessing_defines)

cpp_preprocessing_defines := -D BREATH_SYSTEM=$(system)      \
                             -D BREATH_COMPILER=$(compiler)

bin_root := $(root)/bin
dependent_subdir := $(system)/$(compiler)
bin_dir := $(bin_root)/$(dependent_subdir)
exe_dir := $(bin_dir)
         # ^^^^ variant debug/release?

include $(root)/makefile/$(compiler).mk
include $(root)/makefile/$(system).mk

#       Common targets
# ----------------------------------------------------------------------------
.PHONY: all
all: $(bin_dir)
	$(do_for_all_subdirs)
.PHONY: clean
clean:
	$(do_for_all_subdirs)

$(bin_dir):
	mkdir -p $(bin_dir)

#       Automatic dependency generation; the method used here is
#       described in:
#
#         <http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/>.
# ----------------------------------------------------------------------------
dependency_dir := .dependency/$(dependent_subdir)
$(shell mkdir -p $(dependency_dir) > /dev/null)
post_compile = @mv -f $(dependency_dir)/$*.temp_dep $(dependency_dir)/$*.dep \
                 && touch $@

$(bin_dir)/%$(object_file_suffix): %.cpp
$(bin_dir)/%$(object_file_suffix): %.cpp $(dependency_dir)/%.dep
	$(compile_to_dependency)
	$(compile_to_object)
	$(post_compile)

$(dependency_dir)/%.dep: ;
.PRECIOUS: $(dependency_dir)/%.dep

include $(wildcard $(patsubst %,$(dependency_dir)/%.dep,    \
                     $(basename $(source_files))))

# Local Variables:
# mode: makefile
# indent-tabs-mode: nil
# End:
# vim: set ft=make et sts=4 sw=4:
