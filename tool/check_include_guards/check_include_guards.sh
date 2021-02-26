#! /bin/sh --
# ============================================================================
#                         Copyright 2021 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________
#
#       This script checks for mishaps in our include guards.
#       Specifically, that every .hpp file has one guard (and only one),
#       and that the names of the guarding macros are all distinct.
#
#       It is tailored to our coding style, and is particularly simple,
#       given that we don't use conditional compilation for anything
#       else than include guards.
#
#       Note that it doesn't handle file names whose path relative to
#       the Breeze root contains spaces (it's OK if the Breeze root path
#       contains spaces, though). Also, it ignores empty .hpp files (if
#       any).
# ----------------------------------------------------------------------------

set -eu

root="../.."
include_file_pattern="*.hpp"

get_include_file_name_list()
{
    #       TODO:
    #
    #        - Due to this function, this script doesn't work when using
    #          the Visual Studio command prompt (use_cygwin tool),
    #          because it will then attempt to use the Windows `find`
    #          command, instead of the Cygwin one.
    #
    #          For the moment, we just don't run the script on Windows.
    # ------------------------------------------------------------------------
    find "$root" -name "$include_file_pattern" \! -type d
}

awk '
    function make_readable( n )
    {
        return n == 0 ? "no" : n
    }

    function remove_last_char( s )
    {
        return substr( s, 1, length( s ) - 1 )
    }

    BEGIN {
        exit_error = 2
        separator = "\n"

        exit_code  = 0
    }

    FNR == 1 {
        guard_counts[ FILENAME ] = 0
    }

    $1 == "#ifndef" && $2 ~ /^BREEZE_GUARD_[a-zA-Z0-9]/ {
        ++ guard_counts[ FILENAME ]
        guard_map[ $2 ] = guard_map[ $2 ] FILENAME separator
    }

    END {
        for ( file_name in guard_counts ) {
            count = guard_counts[ file_name ]
            if ( count != 1 ) {
                printf( "Error: %s Breeze guards in %s\n",
                        make_readable( count ), file_name )
                exit_code = exit_error
            }
        }

        for ( macro_name in guard_map ) {
            guard_map[ macro_name ] = remove_last_char( guard_map[ macro_name ] )
            count = split( guard_map[ macro_name ], file_names, separator )
            if ( count != 1 ) {
                printf( "Error: macro name %s duplicated in:\n", macro_name )
                for ( i in file_names ) {
                    printf( "   %s\n", file_names[ i ] )
                }

                exit_code = exit_error
            }
        }

        exit exit_code
    }
' ` get_include_file_name_list `
