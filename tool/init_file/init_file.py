#! /usr/bin/env python3
# ============================================================================
#                         Copyright 2021 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________

"""
        Initializes a text file for Breeze.

        This script must be used to initialize all text files intended
        for Breeze. It ensures, among other things, that a copyright
        notice and the license reference (plus, guards for C++ includes)
        are inserted. See the top-level Breeze read_me for further
        details.
"""

#       Maintenance note:
#       -----------------
#
#           Keep the following files in sync:
#
#            - .editorconfig
#            - .gitattributes
#            - init_file.py
#            - language_traits.txt
# ----------------------------------------------------------------------------

from make_copyright_notice  import  make_copyright_notice
from quit_script            import  quit_script
import enum
import os
import re
import subprocess
import sys

#       The string used in language_traits.txt to indicate absence.
# ----------------------------------------------------------------------------
g_absent = "no"

#       Maximum number of characters per line (for all files).
# ----------------------------------------------------------------------------
g_line_width = 78


def file_name_extension( file_name ):
    return os.path.splitext( file_name )[ 1 ]


class language_traits:
    def __init__( self, traits_list ):
        self.comment_start = traits_list[ 1 ]
        self.comment_end   = traits_list[ 2 ]
        self.line_comment  = traits_list[ 3 ]
        self.language_name = traits_list[ 4 ]


def get_language_traits( file_name ):
    traits_file_path = os.environ[ "BREEZE_ROOT" ] +    \
        "/tool/init_file/language_traits.txt"

    result = None
    for line in open( traits_file_path ):
        if not line.startswith( "#" ):
            traits = line.split()
            if len( traits ) > 0 :
                regex = traits[ 0 ]
                if re.match( regex, file_name ):
                    result = language_traits( traits )
                    break

    return result


def get_license_reference():
    #       Note that the name of the license file is explicitly
    #       mentioned, and unambiguous. This is IMHO very useful if
    #       Breeze is distributed together with software having a
    #       different license.
    # ------------------------------------------------------------------------
    return """Licensed under the 3-Clause BSD License.
(See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
<https://opensource.org/licenses/BSD-3-Clause>.)"""


def get_pvs_studio_text():
    #       This text enables free usage of PVS-Studio. See:
    #
    #         <https://www.viva64.com/en/b/0457/>.
    #
    #       Paul Eremeeff of PVS-Studio said me I could use this
    #       comment, even if Breeze allows commercial usage.
    #
    #       Here's the quote (mail with subject "A report and a
    #       question", dated March 20, 2017):
    #
    #       > 2. My open source project is licensed under the 3-clause
    #       > BSD license, which does not prohibit commercial usage.
    #       > Does the project qualify as a "non-commercial" open source
    #       > project as it concerns using PVS Studio for free? The
    #       > alternative is "independent project of an individual
    #       > developer" but I wouldn't want to exclude the possibility
    #       > that other contributors existed in the future.
    #
    #       Yes, you can use the 'open source non-commercial project'
    #       comment.
    # ------------------------------------------------------------------------
    return """This is an open source non-commercial project.
Dear PVS-Studio, please check it.
PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
http://www.viva64.com"""


def opening_line( language, base_name ):
    if language == "AWK":
        return "#! /bin/awk -f"

    if language == "Batch":
        return "@echo off"

    if language == "CSS":
        return '@charset "UTF-8";'

    if language == "Emacs-Lisp":
        return ";;; " + base_name + " --- TODO: description"

    if language == "Python":
        return "#! /usr/bin/env python3"

    if language == "Shell":
        if file_name_extension( base_name ) != ".shc":
            return "#! /bin/sh --"

    return None


def mark_section( section_type, language_traits ):
    if language_traits.line_comment == g_absent:
        if section_type == "start":
            if language_traits.comment_start != g_absent:
                print( language_traits.comment_start )
        elif section_type == "end":
            if language_traits.comment_end != g_absent:
                print( language_traits.comment_end )
        else:
            quit_script( "internal error (wrong argument to `mark_section()`)" )


class alignment( enum.Enum ):
    left   = 0
    center = 1

def write_with_prefix( text, align, prefix, width ):
    for line in text.splitlines():
        if line == "":
            print( prefix )
        else:
            incipit = prefix + " "
            print( incipit, end = "" )

            if align == alignment.left:
                print( text )
            elif align == alignment.center:
                room = width - len( incipit )
                s = line[ 0 : room ]    # this may truncate

                #       Do not use str.center(), because we want the
                #       number of spaces to the left to be <= the number
                #       of spaces to the right (str.center() does the
                #       opposite, it seems).
                # ------------------------------------------------------------
                space_count = room - len( s )
                spaces_to_left = ' ' * ( space_count // 2 )
                print( spaces_to_left + s )
            else:
                quit_script( "alignment to right not implemented" )


def write_header( traits, base_file_name ):
    opening = opening_line( traits.language_name, base_file_name )
    if opening:
        print( opening )

    mark_section( "start", traits )

    name_extension = file_name_extension( base_file_name )
    ruler1         = "=" * g_line_width
    ruler2         = "_" * g_line_width

    header = ""
    header += ruler1 + "\n"

    if name_extension == ".cpp":
        header += get_pvs_studio_text() + "\n" +    \
                  ruler1 + "\n"

    header += make_copyright_notice( os.environ[ "BREEZE_CONTRIBUTOR" ] ) + "\n\n"
    header += get_license_reference() + "\n"
    header += ruler2

    prefix   = traits.line_comment if traits.line_comment != g_absent else ""
    write_with_prefix( header, alignment.center, prefix, g_line_width )

    if name_extension == ".hpp":
        print( "//" )
        print( "//!     \\file" )
        print( "//!     \\brief")
        length = g_line_width - len( "// " )
        print( "// " + "-" * length )
    elif name_extension == ".py":
        print()
        print( '"""')
        print( "        TODO" )
        print( '"""' )
        length = g_line_width - len( "# " )
        print( "# " + "-" * length )

    mark_section( "end", traits )


def write_body( traits, base_file_name ):
    if traits.language_name == "C++":
        print( "" )
        namespace_definition = "namespace breeze_ns {\n\n}"
        guarded_contents = '#include "breeze/top_level_namespace.hpp"\n\n'  \
                           + namespace_definition
        if file_name_extension( base_file_name ) == ".hpp":
            exe_path = os.environ[ "BREEZE_ROOT" ] + "/bin/include_guard"
            if os.path.isfile( exe_path ) and os.access( exe_path, os.X_OK ):
                sys.stdout.flush()
                proc = subprocess.Popen( [ exe_path ], stdin = subprocess.PIPE )
                proc.communicate( bytes( guarded_contents + "\n", "utf-8" ) )
            else:
                quit_script( "cannot find or execute the include_guard tool;"
                        " did you build it?" )
        else:
            print( namespace_definition )


#       write_trailer():
#       ================
#
#       This trailer is only necessary for the couple of file name
#       extensions (namely .tpp and .shc) that Emacs and Vim don't
#       recognize automatically.
# ----------------------------------------------------------------------------
#
#       Note:
#           About "mode: xx", is Emacs case-sensitive on "xx"??
#           Aesthetically I prefer lowercase, and it seems to work, but
#           the manuals seem to use always uppercase. --gps
# ----------------------------------------------------------------------------
def write_trailer( base_file_name ):
    extension = file_name_extension( base_file_name )
    if extension == ".tpp":
        print ("""
// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:""" )
    elif extension == ".shc":
        print("""
# Local Variables:
# mode: shell-script
# End:
# vim: set ft=sh:""" )
    elif extension == ".el":
        # Not essential but... when in Rome... :-)
        print( "\n;;; " + base_file_name + " ends here" )


def main():
    try:
        argc = len( sys.argv )
        if ( argc != 2 ):
            quit_script( "wrong number of arguments" )

        if "BREEZE_ROOT" not in os.environ                  \
            or "BREEZE_CONTRIBUTOR" not in os.environ       \
            or os.environ[ "BREEZE_ROOT" ] == ""            \
            or os.environ[ "BREEZE_CONTRIBUTOR" ] == "":
                quit_script( "BREEZE_ROOT or BREEZE_CONTRIBUTOR not defined or empty" )

        full_path = sys.argv[ 1 ]
        base_name = os.path.basename( full_path )

        if base_name == "":
            quit_script( "no file name provided" )

        traits = get_language_traits( base_name )

        if not traits:
            quit_script( "file name pattern not found in the traits file" )


        write_header( traits, base_name )
        write_body(   traits, base_name )
        write_trailer(        base_name )

    except Exception as ex:
        quit_script( "an exception occurred: {}".format( ex ) )


if __name__ == "__main__":
    main()
