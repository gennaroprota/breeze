#! /bin/awk -f
# ============================================================================
#                         Copyright 2020 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________
#
#       extract_help.awk:
#       =================
#
#       Extracts the documentation for the available makefile targets.
#       Invoked by GNU Make itself when building the target 'help'.
#
#       Allows for multiline help text for any given target.
#
#       The script is tailored to our commenting and formatting style.
#       E.g. we expect a Make target name to always begin in column 1,
#       and don't consider tab characters. You may need to adapt the
#       script, or at least the regular expressions, if your style is
#       different.
#
#       Warning:
#       --------
#
#       Do not run this manually (it needs to be passed the list of
#       makefiles to parse).
# ----------------------------------------------------------------------------

function do_print_line( first_column_text, help_text )
{
    width = 16
    printf( "%-" width "s%s\n", first_column_text, help_text )
}

BEGIN {
    target_pattern = "^[A-Za-z0-9_-]+ *:([^=]|$)"
    comment_pattern = "^##"
    help_line_count = 0
    FS = "[: ]"
}

$0 ~ comment_pattern " " {
    ++ help_line_count

    current_comment_text = $0
    sub( comment_pattern " +", "", current_comment_text )

    help_lines[ help_line_count ] = current_comment_text
}

$0 ~ target_pattern {
    if ( help_line_count != 0 ) {
        do_print_line( $1 ":", help_lines[ 1 ] )

        for ( i = 2 ; i <= help_line_count; ++ i ) {
            do_print_line( "", help_lines[ i ] )
        }

        delete help_lines
        help_line_count = 0
    }
}
