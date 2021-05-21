# ============================================================================
#                         Copyright 2021 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________

include $(root)/makefile/main.mk

target_library          := $(library_dir)/$(library_name_prefix)$(library_name)$(library_name_suffix)
object_files            := $(patsubst %.cpp, $(bin_dir)/%$(object_file_suffix), $(source_files))

$(target_library): $(object_files)
	$(build_library)

.PHONY: clean
clean:
	rm -fr $(dependency_dir)
	rm -f  $(object_files)
	rm -f  $(target_library)
