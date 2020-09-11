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
#       Does not allow for multiline help text for any given target.
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

BEGIN {
    target_pattern = "^[A-Za-z0-9_-]+ *:([^=]|$)"
    comment_pattern = "^#"
    current_comment_text = ""
    FS = "[: ]"
    first_column_width = 16
}

$0 ~ comment_pattern " " {
    current_comment_text = $0
    sub( comment_pattern " +", "", current_comment_text )
}

$0 ~ target_pattern {
    if ( current_comment_text != "" ) {
        printf "%-" first_column_width "s%s\n", $1 ":", current_comment_text
        current_comment_text = ""
    }
}

# Local Variables:
# mode: awk
# indent-tabs-mode: nil
# c-basic-offset: 4
# End:
# vim: set ft=awk et sts=4 sw=4:
