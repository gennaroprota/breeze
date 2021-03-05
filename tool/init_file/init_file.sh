#! /bin/sh --
# ============================================================================
#                      Copyright 2007-2008 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________
#
#       This script must be used to initialize all text files intended
#       for Breeze. It ensures, among other things, that our copyright
#       notice and license reference (plus, guards for C++ includes) are
#       inserted. See the documentation for further details.
# ----------------------------------------------------------------------------

set -eu

.   "$BREEZE_ROOT/tool/shell/copyright.shc"
.   "$BREEZE_ROOT/tool/shell/file_name.shc"
.   "$BREEZE_ROOT/tool/shell/new_line.shc"
.   "$BREEZE_ROOT/tool/shell/script.shc"
.   "$BREEZE_ROOT/tool/shell/string.shc"

make_opening_line()
{
    case "$language" in
    AWK)
        printf '%s\n' '#! /bin/awk -f'
        ;;
    Batch)
        printf '%s\n' '@echo off'
        ;;
    CSS)
        printf '%s\n' '@charset "UTF-8";'
        ;;
    Emacs-Lisp)
        printf '%s\n\n' ";;; $base_name --- TODO: description"
        ;;
    Python)
        printf '%s\n' '#! /usr/bin/env python3'
        ;;
    Shell)
        if [ "$name_extension" != 'shc' ]
        then
            printf '%s\n' '#! /bin/sh --'
        fi
        ;;
    XSLT)
        printf '%s\n' '<?xml version="1.0" encoding="UTF-8"?>'
        ;;
    esac
}

mark_section()
{
    if [ -z "$prefix" ]
    then
        case "$1" in
        start)
            printf '%s\n' "$block_comment_start"
            ;;
        end)
            printf '%s\n' "$block_comment_end"
            ;;
        *)
            quit_script 'internal error (wrong argument to mark_section())'
            ;;
        esac
    fi
}

get_line_width()
{
    printf '%s' '78'
}

dump()
{
    #       The variables are passed in the environment to awk only.
    # ------------------------------------------------------------------------
    prefix="$prefix"                        \
    width=` get_line_width `                \
    comment_pattern="$comment_pattern"      \
    alignment="$2"                          \
                  awk -f "$BREEZE_ROOT/tool/init_file/dump_with_prefix.awk" "$1"
}



#       Main
# ============================================================================
if [ -z "$BREEZE_ROOT" ] || [ -z "$BREEZE_CONTRIBUTOR" ]
then
    quit_script '$BREEZE_ROOT or $BREEZE_CONTRIBUTOR not defined or empty'
fi

full_path="$1"
base_name=` base_file_name "$full_path" `
name_extension=` file_name_extension "$full_path" `

if [ -z "$full_path" ]
then
    quit_script 'no file name provided'
fi


#       Find the language corresponding to the name pattern and extract
#       the relevant data about it.
# ----------------------------------------------------------------------------
language=""
traits_file="$BREEZE_ROOT/tool/init_file/language_traits.txt"
comment_pattern='^[:space:]*#'

eval ` awk '
    /'"$comment_pattern"'/ {
        next
    }
    NF > 4 && "'"$full_path"'" ~ $1 {
        printf( "block_comment_start='\''%s'\''\n", $2 )
        printf(   "block_comment_end='\''%s'\''\n", $3 )
        printf(  "line_comment_start='\''%s'\''\n", $4 )
        printf(            "language='\''%s'\''\n", $5 )

        exit

    }' "$traits_file" `

if [ -z "$language" ]
then
    quit_script "file name pattern not found in $traits_file"
fi

absent='no'
prefix=""
if [ "$line_comment_start" != "$absent" ]
then
    prefix="$line_comment_start"
fi

tool_root="$BREEZE_ROOT/tool"
exe_root="$BREEZE_ROOT/bin"

#       Header
# ----------------------------------------------------------------------------
make_opening_line
mark_section start

width=` get_line_width `
(
    row1=` make_string "$width" '=' `
    row2=` make_string "$width" '_' `

    if [ "$name_extension" = 'cpp' ]
    then
        printf '%s\n' "$row1"
        cat "$tool_root/init_file/pvs_studio_text.txt"
    fi

    printf '%s\n' "$row1"
    make_copyright_notice "$BREEZE_CONTRIBUTOR"
    new_line '1'
    cat "$tool_root/init_file/license_reference.txt"
    printf '%s\n' "$row2"
)                                                       | dump - 'align_center'

if [ "$name_extension" = 'hpp' ]
then
    length=`expr "$width" - 3`
    row=` make_string "$length" '-' `
    printf '%s\n' "//"
    printf '%s\n' "//!     \\file"
    printf '%s\n' "//!     \\brief"
    printf '%s\n' "// $row"
fi

if [ "$name_extension" = 'sh' ]
then
    printf '\n'
    printf '%s\n' "set -eu"
fi

mark_section end

#       Body
# ----------------------------------------------------------------------------
blank_lines='8'                      # gps do we single-quote number-literals?
if [ "$language" = 'C++' ]
then
    if [ "$name_extension" = 'hpp' ]
    then
        if [ -x "$exe_root/include_guard" ]
        then
            new_line 1
            (printf '\n#include "breeze/top_level_namespace.hpp"\n';
             printf '\nnamespace breeze_ns {'; new_line "$blank_lines"; printf '}\n') |
                "$exe_root/include_guard"
            new_line 1
        else
            printf '%s\n' "Cannot find or execute the include_guard tool. Did you build it?"
        fi
    else
        printf '\nnamespace breeze_ns {\n\n}\n\n'
    fi
else
    new_line "$blank_lines"
fi
#       Trailer
#
#       This used to invoke a separate script to add a trailer that set
#       indent width and other variables, including the file type, for
#       Vim and Emacs. In fact, setting the file type was only necessary
#       for the couple of extensions (namely .tpp and .shc) that Emacs
#       and Vim don't recognize automatically, but, while we were at it,
#       we set it always.
#
#       At a point, anyway, we switched to EditorConfig, which makes
#       things easier and works with more editors. This made most of the
#       trailer unnnecessary, except that we still need to set the file
#       type for those two extensions. So we add a trailer for them
#       (only), here.
# ----------------------------------------------------------------------------
#
#       Note:
#           About "mode: xx", is Emacs case-sensitive on "xx"??
#           Aesthetically I prefer lowercase, and it seems to work, but
#           the manuals seem to use always uppercase. --gps
# ----------------------------------------------------------------------------
if [ "$name_extension" = "tpp" ]
then
    mark_section start
    printf '%s\n%s\n%s\n%s\n'   \
        "Local Variables:"      \
        "mode: c++"             \
        "End:"                  \
        "vim: set ft=cpp:"          | dump - 'align_left'
    mark_section end
elif [ "$name_extension" = "shc" ]
then
    mark_section start
    printf '%s\n%s\n%s\n%s\n'   \
        "Local Variables:"      \
        "mode: shell-script"    \
        "End:"                  \
        "vim: set ft=sh:"           | dump - 'align_left'
    mark_section end
fi

if [ "$language" = 'Emacs-Lisp' ]
then
    # Not essential but... when in Rome... :-)
    printf '\n%s\n' ";;; $base_name ends here"
fi
