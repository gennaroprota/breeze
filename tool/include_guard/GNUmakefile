# Author: Gennaro Prota
# gps add boilerplate!!

root := ../..

target = include_guard
libraries = advapi32.lib
            ##gps temp! (Windows only :-() --coupled with msvc.mk!!!

all: $(target)

vpath %.cpp     $(root)/breath/diagnostics/brt  \
                $(root)/breath/path/brt         \
                $(root)/breath/process/brt      \
                $(root)/breath/random/brt       \
                $(root)/breath/text/brt

source_files := main.cpp                        \
                macro_name.cpp                  \
                                                \
                assert.cpp                      \
                exception.cpp                   \
                last_api_error.cpp              \
                                                \
                allowed_path_separators.cpp     \
                base_file_name.cpp              \
                                                \
                command_line.cpp                \
                exit_code.cpp                   \
                program.cpp                     \
                program_option.cpp              \
                                                \
                entropy_source.cpp              \
                subrange_max.cpp                \
                                                \
                begins_with.cpp


$(target): $(patsubst %.cpp, %.o, $(source_files))
	$(link_to_exec)

include $(root)/makefile/start.mk
