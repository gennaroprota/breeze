# ============================================================================
#                         Copyright 2021 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________

import os
import sys

def _get_script_name():
    """
    Returns the non-directory portion of the running script's path.
    """

    return os.path.basename( sys.argv[ 0 ] )


def quit_script( text ):
    """
    Exits the running script with a failure code (non-zero).

    Keyword arguments:
        text:               A string to be output.

    If `text` is a non-empty string, then a message is output to
    `stderr` including that string. The messages ends with a newline.
    """
    if text != "":
        script_name = _get_script_name()
        prefix = script_name if script_name != "" else "<no name>"

        sys.stderr.write( "{}: {}\n".format( prefix, text ) )

    sys.exit( 2 )
