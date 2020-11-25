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


#       libraries:      (Optional.)
#
#                       A space-separated list with the names of the
#                       libraries to link with.
#
#                       Since Clang and GCC want the library names (-l
#                       option) without prefix and suffix, and since
#                       adding is easier than removing in GNU Make, the
#                       names in the list must be specified without
#                       prefix and suffix (they will be added where
#                       needed; for instance, suffixes will be added in
#                       msvc.mk).
# ----------------------------------------------------------------------------


#       Rationale:
#
#       this is almost always what one wants; see:
#
#         <https://www.gnu.org/software/make/manual/html_node/Errors.html>.
# ----------------------------------------------------------------------------
.DELETE_ON_ERROR:


.SHELLFLAGS += -e -u
MAKEFLAGS += --warn-undefined-variables
.DEFAULT_GOAL := all

has_triplet := no
ifneq ($(and $(compiler), $(system)),)
    has_triplet := yes
endif
export has_triplet

define require_triplet
    if [ $$has_triplet = "no" ] ; then                                         \
        printf '%s%s\n' "Please, define 'system' and 'compiler' on the"        \
            " command line; e.g. run 'system=unix compiler=gcc make <target>'";\
        exit 2 ;                                                               \
    fi
endef

default_architecture := x86_64

ifndef architecture
    architecture := $(default_architecture)
endif

ifeq ($(architecture),)
    architecture := $(default_architecture)
endif

#       do_for_all_subdirs():
#       =====================
#
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


include_dir := $(root)

ifndef cpp_extra_options
    #       Silences warnings. (It's normal for this variable to be
    #       undefined.)
    # ------------------------------------------------------------------------
    cpp_extra_options :=
endif

ifndef libraries
    #       Likewise.
    # ------------------------------------------------------------------------
    libraries :=
endif

cpp_options = $(cpp_basic_options)                  \
              $(cpp_debug_options)                  \
              $(cpp_extra_options)                  \
              $(include_switch)"$(include_dir)"     \
              $(cpp_preprocessing_defines)

cpp_preprocessing_defines := -D BREEZE_SYSTEM=$(system)      \
                             -D BREEZE_COMPILER=$(compiler)

bin_root := $(root)/bin
dependent_subdir := $(architecture)/$(system)/$(compiler)
bin_dir := $(bin_root)/$(dependent_subdir)
exe_dir := $(bin_dir)
         # ^^^^ variant debug/release?


ifeq ($(has_triplet),yes)
    include $(root)/makefile/$(system).mk
    include $(root)/makefile/$(compiler).mk
endif

#       Automatic dependency generation:
#       ================================
#
#       The method used here is described in:
#
#         <http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/>.
#
#       It has, among others, the following properties (well explained
#       in the aforementioned article):
#
#        - dependency files will be kept; Make will not consider them
#          just intermediate files and delete them
#
#        - if a dependency file is deleted without modifying any source
#          files, Make will recreate it
#
#        - if the build is killed at the "wrong" moment, causing a
#          dependency file to be corrupted, the dependency file isn't
#          actually used (see $(post_compile))
# ----------------------------------------------------------------------------
dependency_dir := .mkdep/$(dependent_subdir)
post_compile = mv -f $(dependency_dir)/$*.temp_dep $(dependency_dir)/$*.dep \
                 && touch $@

$(bin_dir)/%$(object_file_suffix): %.cpp
$(bin_dir)/%$(object_file_suffix): %.cpp $(dependency_dir)/%.dep  |  $(dependency_dir)
	$(compile_to_dependency)
	$(compile_to_object)
	$(post_compile)

$(dependency_dir): ; mkdir -p $@

dependency_files := $(patsubst %,$(dependency_dir)/%.dep, $(basename $(source_files)))

$(dependency_files):

include $(wildcard $(dependency_files))

#       Documentation generation:
#       =========================
#
#       For convenience, we provide two target names: 'documentation'
#       and 'doc' (names meant for user consumption are almost never
#       abbreviated in Breeze, but the documentation folder name is; so,
#       some user will expect the full name, others will expect the same
#       name as the folder).
# ----------------------------------------------------------------------------

##      The same as 'documentation'.
##
.PHONY: doc documentation
doc: documentation

##      Builds the Doxygen documentation.
##
documentation:
	$(root)/tool/build_docs/build_docs.sh "` pwd `"

#       Help target:
#       ============
#
#       See extract_help.awk for more info.
# ----------------------------------------------------------------------------

##      Shows brief documentation about the available targets.
##
.PHONY: help
help:
	$(info )
	$(info Available targets:)
	$(info ------------------)
	$(info )
	@$(root)/makefile/extract_help.awk $(MAKEFILE_LIST)

# Local Variables:
# mode: makefile
# indent-tabs-mode: nil
# End:
# vim: set ft=make et sts=4 sw=4:
