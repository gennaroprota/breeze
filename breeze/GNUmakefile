# ============================================================================
#                      Copyright 2019-2020 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________

root := ..

#       Using vpath is a temporary solution; it doesn't work in case
#       there exist homonym files.
#
#       But, for now, we have no homonyms.
# ----------------------------------------------------------------------------
vpath %.cpp     $(root)/breeze/checksum/brz         \
                $(root)/breeze/conversion/brz       \
                $(root)/breeze/cpu/brz              \
                $(root)/breeze/cryptography/brz     \
                $(root)/breeze/diagnostics/brz      \
                $(root)/breeze/environment/brz      \
                $(root)/breeze/memory/brz           \
                $(root)/breeze/metric/brz           \
                $(root)/breeze/path/brz             \
                $(root)/breeze/process/brz          \
                $(root)/breeze/random/brz           \
                $(root)/breeze/stream/brz           \
                $(root)/breeze/testing/brz          \
                $(root)/breeze/text/brz             \
                $(root)/breeze/time/brz             \
                $(root)/breeze/time/private/brz     \
                $(root)/breeze/uuid/brz

ifeq ($(system),windows)
    vpath %.cpp $(root)/breeze/environment/windows_only/brz \
                $(root)/breeze/time/windows_only/brz
endif

source_files := luhn.cpp                                    \
                                                            \
                roman.cpp                                   \
                                                            \
                hashing_count.cpp                           \
                md5.cpp                                     \
                sha1.cpp                                    \
                sha224.cpp                                  \
                sha256.cpp                                  \
                sha384.cpp                                  \
                sha512.cpp                                  \
                                                            \
                assert.cpp                                  \
                last_api_error.cpp                          \
                                                            \
                get_all_environment_variables.cpp           \
                get_environment_variable.cpp                \
                operating_system_name.cpp                   \
                                                            \
                get_amount_of_physical_memory.cpp           \
                                                            \
                damerau_levenshtein_distance.cpp            \
                levenshtein_distance.cpp                    \
                                                            \
                base_file_name.cpp                          \
                extension.cpp                               \
                get_directory_separators.cpp                \
                                                            \
                exit_code.cpp                               \
                get_current_directory.cpp                   \
                program.cpp                                 \
                set_current_directory.cpp                   \
                                                            \
                entropy_source.cpp                          \
                max_for_subrange.cpp                        \
                                                            \
                inserter.cpp                                \
                null_stream.cpp                             \
                                                            \
                assert_failure.cpp                          \
                stream_reporter.cpp                         \
                test_descriptor.cpp                         \
                test_failure.cpp                            \
                test_reporter.cpp                           \
                test_runner.cpp                             \
                                                            \
                begins_with.cpp                             \
                ends_with.cpp                               \
                printable_string.cpp                        \
                remove_from_end.cpp                         \
                replace_all.cpp                             \
                set_of_chars.cpp                            \
                split.cpp                                   \
                string_constant.cpp                         \
                tail.cpp                                    \
                to_lowercase.cpp                            \
                to_uppercase.cpp                            \
                trim.cpp                                    \
                trim_head.cpp                               \
                trim_tail.cpp                               \
                                                            \
                c_clock_policy.cpp                          \
                steady_clock_timer.cpp                      \
                time_string.cpp                             \
                thread_safe_reentrant_time_functions.cpp    \
                                                            \
                uuid.cpp

ifeq ($(system),windows)
    source_files +=                                         \
                get_operating_system_id.cpp                 \
                operating_system_id.cpp                     \
                windows_version_info.cpp                    \
                                                            \
                performance_counter_policy.cpp
endif

has_cpuid := no
ifeq ($(architecture),x86)
    has_cpuid := yes
endif
ifeq ($(architecture),x86_64)
    has_cpuid := yes
endif

ifeq ($(has_cpuid),yes)
    source_files += get_cpuid_info.cpp
endif

include $(root)/makefile/main.mk

target := $(bin_dir)/$(library_name_prefix)breeze$(library_name_suffix)
object_files :=                                                             \
    $(patsubst %.cpp, $(bin_dir)/%$(object_file_suffix), $(source_files))


$(target): $(object_files)
	$(build_library)

define assemble_to_object
    as --warn --fatal-warnings -o $@ $<
endef

$(bin_dir)/%$(object_file_suffix): %.asm
	$(assemble_to_object)

.PHONY: all
all: $(target)

.PHONY: clean
clean:
	rm -fr $(dependency_dir)
	rm -f $(object_files)
	rm -f $(target)
