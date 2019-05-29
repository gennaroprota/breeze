# Author: Gennaro Prota
# gps add boilerplate!!

root := ../..

target = include_guard
libraries = advapi32.lib
            ##gps temp! (Windows only :-() --coupled with msvc.mk!!!

all: $(target)

vpath %.a       $(root)/bin # Note: update this when we'll separate
                            #       the build directories -gps

source_files := main.cpp                        \
                macro_name.cpp                  \

$(target): $(patsubst %.cpp, %.o, $(source_files)) breath.a
	$(link_to_exec)

include $(root)/makefile/start.mk
