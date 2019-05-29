# Author: Gennaro Prota
# gps add boilerplate!!

root := ../..

include $(root)/makefile/start.mk

target = include_guard$(binary_name_suffix)

libraries = advapi32.lib
            ##gps temp! (Windows only :-() --coupled with msvc.mk!!!

all: $(target)


vpath %$(library_name_suffix) $(root)/bin # Note: update this when we'll separate
                                          #       the build directories -gps

source_files := main.cpp                        \
                macro_name.cpp                  \

breath_library = $(library_name_prefix)breath$(library_name_suffix)

$(target): $(patsubst %.cpp, %.o, $(source_files)) $(breath_library)
	$(link_to_exec)

clean:
	rm -fr .dependency/
	rm -f $(patsubst %.cpp, %.o, $(source_files))
	rm -f $(target)
