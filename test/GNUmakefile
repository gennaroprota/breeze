# ============================================================================
#                         Copyright 2020 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________


root := ..

vpath %.cpp     $(root)/breath/algorithm/test               \
                $(root)/breath/alignment/test               \
                $(root)/breath/checksum/test                \
                $(root)/breath/conversion/test              \
                $(root)/breath/counting/test                \
                $(root)/breath/cpu/test                     \
                $(root)/breath/cryptography/test            \
                $(root)/breath/debugging/test               \
                $(root)/breath/diagnostics/test             \
                $(root)/breath/encoding/test                \
                $(root)/breath/endianness/test              \
                $(root)/breath/environment/test             \
                $(root)/breath/idiom/test                   \
                $(root)/breath/iteration/test               \
                $(root)/breath/mathematics/test             \
                $(root)/breath/memory/test                  \
                $(root)/breath/meta/test                    \
                $(root)/breath/metric/test                  \
                $(root)/breath/operator/test                \
                $(root)/breath/path/test                    \
                $(root)/breath/porting/test                 \
                $(root)/breath/preprocessing/test           \
                $(root)/breath/process/test                 \
                $(root)/breath/random/test                  \
                $(root)/breath/stream/test                  \
                $(root)/breath/testing/test                 \
                $(root)/breath/text/test                    \
                $(root)/breath/time/test                    \
                $(root)/breath/type_identification/test     \
                $(root)/breath/uuid/test                    \
                $(root)/breath/vocabulary/test              \
                $(root)/breath/workaround/test


source_files := unit_test_main.cpp                          \
                                                            \
                crc32_test.cpp                              \
                luhn_test.cpp                               \
                                                            \
                bit_cast_test.cpp                           \
                roman_test.cpp                              \
                                                            \
                digest_ordering_test.cpp                    \
                merkle_damgard_hashing_test.cpp             \
                nist_vectors_test.cpp                       \
                sha384_test.cpp                             \
                                                            \
                dump_expression_test.cpp                    \
                                                            \
                assert_test.cpp                             \
                exception_test.cpp                          \
                                                            \
                base64_to_binary_test.cpp                   \
                binary_to_base64_test.cpp                   \
                                                            \
                endian_codec_test.cpp                       \
                                                            \
                environment_variable_consistency_test.cpp   \
                get_environment_variable_test.cpp           \
                                                            \
                clamp_test.cpp                              \
                count_bits_test.cpp                         \
                digital_root_test.cpp                       \
                gcd_test.cpp                                \
                is_power_of_2_test.cpp                      \
                lcm_test.cpp                                \
                representation_in_base_test.cpp             \
                rounded_up_quotient_test.cpp                \
                                                            \
                auto_array_test.cpp                         \
                                                            \
                is_2s_complement_test.cpp                   \
                                                            \
                damerau_levenshtein_distance_test.cpp       \
                levenshtein_distance_test.cpp               \
                                                            \
                base_file_name_test.cpp                     \
                extension_test.cpp                          \
                                                            \
                prevent_macro_expansion_test.cpp            \
                stringize_after_expansion_test.cpp          \
                stringize_test.cpp                          \
                                                            \
                entropy_source_test.cpp                     \
                subrange_max_test.cpp                       \
                                                            \
                eof_value_test.cpp                          \
                null_stream_test.cpp                        \
                stream_equivalent_test.cpp                  \
                                                            \
                begins_with_test.cpp                        \
                ends_with_test.cpp                          \
                from_string_test.cpp                        \
                printable_string_test.cpp                   \
                remove_from_end_test.cpp                    \
                replace_all_test.cpp                        \
                set_of_chars_test.cpp                       \
                split_test.cpp                              \
                tail_test.cpp                               \
                to_lowercase_test.cpp                       \
                to_string_test.cpp                          \
                to_uppercase_test.cpp                       \
                trim_head_test.cpp                          \
                trim_tail_test.cpp                          \
                                                            \
                readable_type_name_test.cpp                 \
                                                            \
                uuid_test.cpp                               \
                maybe_test.cpp


include $(root)/makefile/main.mk

target := $(bin_dir)/breath_test$(exe_name_suffix)
breath_library := $(bin_dir)/$(library_name_prefix)breath$(library_name_suffix)

$(target): $(patsubst %.cpp, $(bin_dir)/%$(object_file_suffix), \
                $(source_files))                                \
           $(breath_library)
	$(link_to_exec)

.PHONY: all test test-run
all:        test test-run

test:       $(target)

test-run:   test
	$(bin_dir)/breath_test

# Local Variables:
# mode: makefile
# indent-tabs-mode: nil
# End:
# vim: set ft=make et sts=4 sw=4:
