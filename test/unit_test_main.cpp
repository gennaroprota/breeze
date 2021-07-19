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
#include "breeze/diagnostics/assert.hpp"
#include "breeze/diagnostics/last_api_error.hpp"
#include "breeze/environment/operating_system_name.hpp"
#include "breeze/memory/get_amount_of_physical_memory.hpp"
#include "breeze/process/exit_code.hpp"
#include "breeze/process/program.hpp"
#include "breeze/testing/assert_failure.hpp"
#include "breeze/text/replace_all.hpp"
#include "breeze/time/format_time.hpp"
#include "breeze/time/process_stopwatch.hpp"
#include <chrono>
#include <iostream>
#include <sstream>

namespace {

using               clock_type = std::chrono::system_clock ;

[[ noreturn ]] void
unit_test_assert_handler( char const *,
                          char const *,
                          long )
{
    throw breeze::assert_failure() ;
}

std::string
describe_time( clock_type::time_point const & t )
{
    std::string const   format = "%A, %B %e, %Y %I:%M:%S %p UTC" ;

    std::ostringstream  oss ;
    breeze::format_time( format, oss, breeze::time_kind::utc, t ) ;

    return ! oss.fail()
        ? breeze::replace_all( oss.str(), "  ", " " ) // since %e may add a leading space
        : "n/a"
        ;
}

}

namespace breeze_ns {

std::string
get_program_name()
{
    return "Breeze unit tests" ;
}

}

int
main()
{
    using               test_function_type = int () ;

    breeze::set_assert_handler( unit_test_assert_handler ) ;

    test_function_type * const
                        tests[] = {
            test_array_pointer,
            test_breeze_assert,
            test_base64_to_binary,
            test_begins_with,
            test_binary_to_base64,
            test_bit_cast,
            test_ceiling_of_quotient,
            test_counter,
            test_crc,
            test_damerau_levenshtein_distance,
            test_digest_ordering,
            test_digital_root,
            test_breeze_dump_expression,
            test_endian_codec,
            test_ends_with,
            test_entropy_source,
            test_environment_variable_consistency,
            test_eof_value,
            test_format_time,
            test_from_string,
            test_gcd,
            test_get_environment_variable,
            test_get_set_current_directory,
            test_is_2s_complement,
            test_is_power_of_2,
            test_last_api_error,
            test_lcm,
            test_levenshtein_distance,
            test_luhn,
            test_max_for_subrange,
            test_maybe,
            test_merkle_damgard_hashing,
            test_nist_vectors,
            test_null_stream,
            test_population_count,
            test_breeze_prevent_macro_expansion,
            test_printable_string,
            test_readable_type_name,
            test_remove_from_end,
            test_replace_all,
            test_representation_in_base,
            test_roman,
            test_set_of_chars,
            test_sha384,
            test_split,
            test_stream_equivalent,
            test_breeze_stringize,
            test_breeze_stringize_after_expansion,
            test_tail,
            test_to_lowercase,
            test_to_string,
            test_to_uppercase,
            test_trim_head,
            test_trim_tail,
            test_uuid,
            test_width
    } ;

    clock_type::time_point const
                        start_time = clock_type::now() ;
    breeze::process_stopwatch
                        process_stopwatch ;
    int                 failure_count = 0 ;
    for ( test_function_type * f : tests ) {
        int const           exit_code = f() ;
        if ( exit_code != breeze::exit_success ) {
            ++ failure_count ;
        }
    }
    breeze::set_assert_handler( breeze::default_assert_handler ) ;

    breeze::process_duration const
                        process_time = process_stopwatch.elapsed() ;
    clock_type::time_point const
                        end_time = clock_type::now() ;

    if ( failure_count == 0 ) {
        std::cout << "All tests passed." ;
    } else {
        std::cout << failure_count << " components have tests that FAILED." ;
    }

    std::cout << std::endl ;

    //      We output the detected operating system description here,
    //      because the operating_system_name class is basically
    //      untestable. We hope that, this way, the user can notice if
    //      something is wrong.
    // -----------------------------------------------------------------------
    std::cout << "\nDetected operating system: " <<
        breeze::operating_system_name() << std::endl ;

    //      Likewise for the amount of physical memory (use floating
    //      point to let the user notice if the amount is not a multiple
    //      of 1024)...
    // -----------------------------------------------------------------------
    auto const          amount = static_cast< double >(
            breeze::get_amount_of_physical_memory() ) / 1024.0 ;
    std::cout << "\nAmount of physical memory in MiB: " <<
        amount << std::endl ;

    //      ... for the last API error...
    // -----------------------------------------------------------------------
    std::cout << "\nLast API error: " <<
        breeze::last_api_error( "Unit tests" ) << std::endl ;

    std::cout << '\n' ;
    std::cout << "Started at:  " << describe_time( start_time ) << std::endl ;
    std::cout << "Finished at: " << describe_time(   end_time ) << std::endl ;
    std::cout << "Elapsed:     " <<
        std::chrono::duration_cast<
            std::chrono::duration< double > >( end_time - start_time ).count() <<
        's' << std::endl ;

    //      ... and for the `process_stopwatch` times.
    // -----------------------------------------------------------------------
    std::cout << "Process times:" << std::endl ;
    std::cout << process_time     << std::endl ;

    int const           exit_code = breeze::program::instance().exit_code() ;
    if ( exit_code != 0 ) {
        std::cout << "NOTE: program::exit_code() was set to "
            << exit_code << std::endl ;
    }

    std::cout << std::endl ;

    return failure_count == 0 && exit_code == 0
        ? breeze::exit_success
        : breeze::exit_error
        ;
}
