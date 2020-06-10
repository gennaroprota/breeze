// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "unit_test_main.hpp"
#include <cstdlib>
#include <iostream>

int
main()
{
    using               test_function_type = int () ;

    test_function_type * const
                        tests[] = {
            // test_breath_assert, // TODO
            test_auto_array,
            test_base_file_name,
            test_base64_to_binary,
            test_begins_with,
            test_binary_to_base64,
            test_bit_cast,
            test_clamp,
            // test_count_bits, // TODO
            test_crc32,
            test_damerau_levenshtein_distance,
            test_digest_ordering,
            test_digital_root,
            test_breath_dump_expression,
            test_endian_codec,
            test_ends_with,
            test_entropy_source,
            test_environment_variable_consistency,
            test_eof_value,
            test_exception,
            test_extension,
            test_from_string,
            // test_gcd, // TODO
            test_get_environment_variable,
            test_is_2s_complement,
            test_is_power_of_2,
            // test_lcm, // TODO
            test_levenshtein_distance,
            test_luhn,
            test_maybe,
            test_merkle_damgard_hashing,
            test_nist_vectors,
            test_null_stream,
            test_breath_prevent_macro_expansion,
            test_printable_string,
            test_readable_type_name,
            test_remove_from_end,
            test_replace_all,
            test_representation_in_base,
            test_roman,
            test_rounded_up_quotient,
            test_set_of_chars,
            test_sha384,
            test_split,
            test_stream_equivalent,
            test_breath_stringize,
            test_breath_stringize_after_expansion,
            test_subrange_max,
            test_tail,
            test_to_lowercase,
            test_to_string,
            test_to_uppercase,
            test_trim_head,
            test_trim_tail,
            test_uuid
    } ;

    int                 result = EXIT_SUCCESS ;
    for ( auto const & f : tests )
    {
        int                 exit_code = f() ;
        if ( exit_code != EXIT_SUCCESS ) {
            result = EXIT_FAILURE ;
        }
    }

    std::cout << ( result == EXIT_SUCCESS
        ? "All tests passed."
        : "At least one test FAILED." ) << std::endl ;
        ;

    return result ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
