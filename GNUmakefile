# ============================================================================
#                         Copyright 2013 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________
#
#       Breeze Library - Root makefile (for GNU Make)
# ----------------------------------------------------------------------------

subdirs := breeze   \
           test     \
           tool

root := .
include $(root)/makefile/main.mk

ruler := \
------------------------------------------------------------------------------

#       Common targets
# ----------------------------------------------------------------------------

##      Builds the library, runs the unit tests and builds the tools,
##      for a given architecture/system/compiler triplet and build type.
##      This is the default target, and requires `system`, `compiler`
##      and `build_type` to be defined.
# ----------------------------------------------------------------------------
.PHONY: all
all: $(bin_dir)
	$(info $(ruler))
	$(info Using $(compiler_display_name) $(compiler_version))
	@printf '%s\n' "Running on: $$( uname -m )"
	$(do_for_all_subdirs)

##      Deletes the build artifacts for a given triplet and build type
##      (see `all`). Requires `system`, `compiler` and `build_type` to
##      be defined.
# ----------------------------------------------------------------------------
.PHONY: clean
clean:
	@$(require_build_parameters)
	$(do_for_all_subdirs)

$(bin_dir):
	@$(require_build_parameters)
	@$(check_compiler_is_found)
	mkdir -p $@

.PHONY: test-run
test-run:
	@$(require_build_parameters)
	$(do_for_all_subdirs)
