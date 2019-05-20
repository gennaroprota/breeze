# ============================================================================
#                      Copyright 2006-2019 Gennaro Prota
#                         Copyright 2000 James Kanze
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________


# This file assumes the following variables are defined:

#  - compiler
#  - subdirs?? -gps


ifeq ($(and $(compiler), $(system)),)
    $(error Please, define 'compiler' and 'system' on the command line)
endif



#
# Function originally taken from James Kanze's GABI Library version 2005v01 (named "doForAll", there).
#
define do_for_all_subdirs
    for x in $(subdirs) ; \
    do \
        $(MAKE) -C $$x $@ || exit $$? ; \
    done
endef



#       Common targets
# ----------------------------------------------------------------------------
.PHONY: all
all:
	$(do_for_all_subdirs)
.PHONY: clean
clean:
	$(do_for_all_subdirs)



include_dir     = $(root)

cpp_options = $(cpp_basic_options) $(cpp_debug_options) $(cpp_extra_options) $(include_switch)"$(include_dir)" \
              $(cpp_preprocessing_defines)

cpp_preprocessing_defines = -D BREATH_ARCHITECTURE=$(arch) -D BREATH_SYSTEM=$(system) -D BREATH_COMPILER=$(compiler)

bin_root = $(root)/bin
bin_dir = $(bin_root)/$(arch)/$(system)/$(compiler)
exe_dir = $(bin_dir)
         # ^^^^ variant debug/release?


#       Automatic dependency generation; the method use here is
#       described in:
#
#         <http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/>.
# ----------------------------------------------------------------------------
dependency_dir := .dependency
$(shell mkdir -p $(dependency_dir) > /dev/null)
post_compile = @mv -f $(dependency_dir)/$*.temp_dep $(dependency_dir)/$*.dep && touch $@

%.o: %.cpp
%.o: %.cpp $(dependency_dir)/%.dep
	$(compile_to_dependency)
	$(compile_to_object)
	$(post_compile)

$(dependency_dir)/%.dep: ;
.PRECIOUS: $(dependency_dir)/%.dep

include $(wildcard $(patsubst %,$(dependency_dir)/%.dep,$(basename $(source_files))))

include $(root)/makefile/$(compiler).mk

# Local Variables:
# mode: makefile
# indent-tabs-mode: nil
# End:
# vim: set ft=make et sts=4 sw=4:
