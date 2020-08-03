# ============================================================================
#                         Copyright 2013 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________
#
#       Breath Library - Root makefile (GNU Make)
# ----------------------------------------------------------------------------

subdirs := breath   \
           test     \
           tool

root := .
include $(root)/makefile/main.mk

ruler := \
------------------------------------------------------------------------------

#       Common targets
# ----------------------------------------------------------------------------
.PHONY: all
all: $(bin_dir)
	$(info $(ruler))
	$(info Using $(compiler_display_name) $(compiler_version))
	$(do_for_all_subdirs)

.PHONY: clean
clean:
	$(do_for_all_subdirs)

$(bin_dir):
	mkdir -p $(bin_dir)

.PHONY: test-run
test-run:
	$(do_for_all_subdirs)

# Local Variables:
# mode: makefile
# indent-tabs-mode: nil
# End:
# vim: set ft=make et sts=4 sw=4:
