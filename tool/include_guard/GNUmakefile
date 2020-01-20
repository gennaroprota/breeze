# ============================================================================
#                         Copyright 2016 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________

root := ../..

source_files := main.cpp                        \
                macro_name.cpp                  \

include $(root)/makefile/main.mk

target := $(bin_dir)/include_guard$(binary_name_suffix)

libraries := advapi32.lib
             ##gps temp! (Windows only :-() --coupled with msvc.mk!!!

.PHONY: all
all: $(target)


breath_library := $(bin_dir)/$(library_name_prefix)breath$(library_name_suffix)

$(target): $(patsubst %.cpp, $(bin_dir)/%$(object_file_suffix), \
               $(source_files))                                 \
           $(breath_library)
	$(link_to_exec)

.PHONY: clean
clean:
	rm -fr $(dependency_dir)
	rm -f $(patsubst %.cpp, $(bin_dir)/%$(object_file_suffix),  \
                                                               $(source_files))
	rm -f $(target)

# Local Variables:
# mode: makefile
# indent-tabs-mode: nil
# End:
# vim: set ft=make et sts=4 sw=4:
