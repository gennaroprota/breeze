# ============================================================================
#                         Copyright 2020 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________


root                    := ..

vpath %.cpp     $(root)/breeze/algorithm/test               \
                $(root)/breeze/alignment/test               \
                $(root)/breeze/checksum/test                \
                $(root)/breeze/conversion/test              \
                $(root)/breeze/counting/test                \
                $(root)/breeze/cpu/test                     \
                $(root)/breeze/cryptography/test            \
                $(root)/breeze/debugging/test               \
                $(root)/breeze/diagnostics/test             \
                $(root)/breeze/encoding/test                \
                $(root)/breeze/endianness/test              \
                $(root)/breeze/environment/test             \
                $(root)/breeze/idiom/test                   \
                $(root)/breeze/iteration/test               \
                $(root)/breeze/mathematics/test             \
                $(root)/breeze/memory/test                  \
                $(root)/breeze/meta/test                    \
                $(root)/breeze/metric/test                  \
                $(root)/breeze/operator/test                \
                $(root)/breeze/path/test                    \
                $(root)/breeze/porting/test                 \
                $(root)/breeze/preprocessing/test           \
                $(root)/breeze/process/test                 \
                $(root)/breeze/random/test                  \
                $(root)/breeze/stream/test                  \
                $(root)/breeze/testing/test                 \
                $(root)/breeze/text/test                    \
                $(root)/breeze/time/test                    \
                $(root)/breeze/type_identification/test     \
                $(root)/breeze/uuid/test                    \
                $(root)/breeze/vocabulary/test              \
                $(root)/breeze/workaround/test


source_files            := unit_test_main.cpp                           \
                                                                        \
                           crc_test.cpp                                 \
                           luhn_test.cpp                                \
                                                                        \
                           bit_cast_test.cpp                            \
                           roman_test.cpp                               \
                                                                        \
                           counter_test.cpp                             \
                                                                        \
                           digest_ordering_test.cpp                     \
                           merkle_damgard_hashing_test.cpp              \
                           nist_vectors_test.cpp                        \
                           sha384_test.cpp                              \
                                                                        \
                           dump_expression_test.cpp                     \
                                                                        \
                           assert_test.cpp                              \
                           last_api_error_test.cpp                      \
                                                                        \
                           base64_to_binary_test.cpp                    \
                           binary_to_base64_test.cpp                    \
                                                                        \
                           endian_codec_test.cpp                        \
                                                                        \
                           environment_variable_consistency_test.cpp    \
                           get_environment_variable_test.cpp            \
                                                                        \
                           ceiling_of_quotient_test.cpp                 \
                           clamp_test.cpp                               \
                           digital_root_test.cpp                        \
                           gcd_test.cpp                                 \
                           is_power_of_2_test.cpp                       \
                           lcm_test.cpp                                 \
                           population_count_test.cpp                    \
                           representation_in_base_test.cpp              \
                                                                        \
                           array_pointer_test.cpp                       \
                                                                        \
                           is_2s_complement_test.cpp                    \
                           width_test.cpp                               \
                                                                        \
                           damerau_levenshtein_distance_test.cpp        \
                           levenshtein_distance_test.cpp                \
                                                                        \
                           base_file_name_test.cpp                      \
                           file_name_extension_test.cpp                 \
                                                                        \
                           prevent_macro_expansion_test.cpp             \
                           stringize_after_expansion_test.cpp           \
                           stringize_test.cpp                           \
                                                                        \
                           get_set_current_directory_test.cpp           \
                                                                        \
                           entropy_source_test.cpp                      \
                           max_for_subrange_test.cpp                    \
                                                                        \
                           eof_value_test.cpp                           \
                           null_stream_test.cpp                         \
                           stream_equivalent_test.cpp                   \
                                                                        \
                           begins_with_test.cpp                         \
                           ends_with_test.cpp                           \
                           from_string_test.cpp                         \
                           printable_string_test.cpp                    \
                           remove_from_end_test.cpp                     \
                           replace_all_test.cpp                         \
                           set_of_chars_test.cpp                        \
                           split_test.cpp                               \
                           tail_test.cpp                                \
                           to_lowercase_test.cpp                        \
                           to_string_test.cpp                           \
                           to_uppercase_test.cpp                        \
                           trim_head_test.cpp                           \
                           trim_tail_test.cpp                           \
                                                                        \
                           format_time_test.cpp                         \
                                                                        \
                           readable_type_name_test.cpp                  \
                                                                        \
                           uuid_test.cpp                                \
                                                                        \
                           maybe_test.cpp


ifeq ($(system),windows)
    additional_libraries+= Advapi32   \
                           User32     \
                           Version
endif

exe_base_name           := breeze_test
libraries               := breeze
include $(root)/makefile/executable.mk

.PHONY: all test test-run check_include_guards
all:        test test-run check_include_guards

test:       $(target)

test-run:   test
	$(bin_dir)/breeze_test

check_include_guards:
	$(root)/tool/check_include_guards/check_include_guards.py $(root)

.PHONY: clean
clean:
	rm -fr $(dependency_dir)
	rm -f $(object_files)
	rm -f $(target)
