#! /bin/sh --
# ============================================================================
#                         Copyright 2020 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________
#
#       Builds the library documentation (using Doxygen).
#
#       Syntax:
#           build_docs breeze_root
#
#       Arguments:
#
#           breeze_root
#
#               Full path to the root directory of the source tree
#               (without any trailing slash).
#
#       Note:
#           normally, there's no need to invoke this script manually: it
#           will be invoked by GNU Make when issuing the command
#
#               make documentation
# ----------------------------------------------------------------------------

set -eu

.   "$BREEZE_ROOT/tool/shell/file_name.shc"
.   "$BREEZE_ROOT/tool/shell/script.shc"


clean_up()
{
    rm -fr "$temp_dir"

    #       These files are created by Doxygen, not by this script. But
    #       sometimes they are not deleted by Doxygen, so let's do that
    #       ourselves.
    # ------------------------------------------------------------------------
    rm -f "$root_dir"/doc/source/doxygen_*db_*.tmp
}

run_doxygen()
{
    breeze_version=` sed -n 's/#define \+BREEZE_VERSION \+\(.\+\)/\1/p'     \
                            "$root_dir/breeze/version.hpp" `

    (
        cat doxygen.cfg
        printf '%s\n' "PROJECT_NUMBER = \"version $breeze_version\""
    ) | doxygen -
}

if [ $# -ne 1 ]
then
    quit_script 'wrong number of arguments.'
fi

if ! doxygen --version >/dev/null
then
    quit_script \
        'could not run Doxygen; is the directory of the exe in your PATH?'
fi


temp_dir=/tmp/` script_name `_$$
trap 'clean_up' 0 1 2 15
mkdir -p "$temp_dir"

root_dir=$1
output_dir="$root_dir/doc"

cd "$root_dir/doc/source"
printf '%s\n' "Using Doxygen ` doxygen --version `"
if ! run_doxygen
then
    quit_script 'an error occurred.'
else
    printf '\n'
    printf '%s\n' 'Documentation built.'
fi

# Local Variables:
# mode: shell-script
# indent-tabs-mode: nil
# sh-indentation: 4
# End:
# vim: set ft=sh et sts=4 sw=4:
