# ============================================================================
#                         Copyright 2019 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________

root := ..

#       Using vpath is a temporary solution; it doesn't work in case
#       there exist homonym files.
#
#       But, for now, the only homonyms are the two integer_log2.hpp's,
#       which don't need to be built.
# ----------------------------------------------------------------------------
vpath %.cpp     $(root)/breath/checksum/brt         \
                $(root)/breath/conversion/brt       \
                $(root)/breath/cryptography/brt     \
                $(root)/breath/diagnostics/brt      \
                $(root)/breath/environment/brt      \
                $(root)/breath/memory/brt           \
                $(root)/breath/metric/brt           \
                $(root)/breath/path/brt             \
                $(root)/breath/process/brt          \
                $(root)/breath/random/brt           \
                $(root)/breath/testing/brt          \
                $(root)/breath/text/brt             \
                $(root)/breath/time/brt             \
                $(root)/breath/uuid/brt

vpath %.asm     $(root)/breath/cpu/brt

source_files := luhn.cpp                            \
                                                    \
                roman.cpp                           \
                                                    \
                hashing_count.cpp                   \
                md5_hasher.cpp                      \
                sha1_hasher.cpp                     \
                sha224_hasher.cpp                   \
                sha256_hasher.cpp                   \
                sha384_hasher.cpp                   \
                sha512_hasher.cpp                   \
                                                    \
                assert.cpp                          \
                exception.cpp                       \
                last_api_error.cpp                  \
                                                    \
                find_environment_string.cpp         \
                get_environment_map.cpp             \
                operating_system_name.cpp           \
                                                    \
                amount_of_physical_memory.cpp       \
                                                    \
                damerau_levenshtein_distance.cpp    \
                levenshtein_distance.cpp            \
                                                    \
                base_file_name.cpp                  \
                directory_separators.cpp            \
                extension.cpp                       \
                                                    \
                child_process.cpp                   \
                command_line.cpp                    \
                current_directory.cpp               \
                exit_code.cpp                       \
                process.cpp                         \
                program.cpp                         \
                program_option.cpp                  \
                set_current_directory.cpp           \
                                                    \
                entropy_source.cpp                  \
                subrange_max.cpp                    \
                                                    \
                console_reporter.cpp                \
                test_descriptor.cpp                 \
                test_exception.cpp                  \
                test_runner.cpp                     \
                                                    \
                begins_with.cpp                     \
                ends_with.cpp                       \
                printable_string.cpp                \
                remove_from_end.cpp                 \
                replace_all.cpp                     \
                set_of_chars.cpp                    \
                split.cpp                           \
                trim.cpp                            \
                trim_head.cpp                       \
                trim_tail.cpp                       \
                                                    \
                c_clock_policy.cpp                  \
                time_string.cpp                     \
                                                    \
                uuid.cpp

asm_source_files := get_cpuid_info.asm              \
                    is_cpuid_supported.asm


include $(root)/makefile/start.mk

target = $(library_name_prefix)breath$(library_name_suffix)

$(target): $(patsubst %.cpp, %.o, $(source_files))  \
             $(patsubst %.asm, %.o, $(asm_source_files))
	$(build_library)

define assemble_to_object
    as --warn --fatal-warnings --32 -o $@ $<
endef

%.o: %.asm
	$(assemble_to_object)


all: $(target)

clean:
	rm -fr .dependency/
	rm -f $(patsubst %.cpp, %.o, $(source_files))
	rm -f $(patsubst %.asm, %.o, $(asm_source_files))
	rm -f $(target)

# Local Variables:
# mode: makefile
# indent-tabs-mode: nil
# End:
# vim: set ft=make et sts=4 sw=4:
