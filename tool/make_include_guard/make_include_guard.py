#! /usr/bin/env python3
# ============================================================================
#                         Copyright 2021 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________

"""
        Generates an include guard (for a new source file or for an
        existing one).

        Synopsis:
        ---------

          make_include_guard [options]

        Limitations:
        ------------

        To add an include guard to an existing file, or to generate one
        for a new file, employ redirection or a pipe: the tool always
        reads from the standard input; and outputs what it reads (if
        anything) to the standard output, enclosed in the classical
        #ifndef/#endif.

        Options:
        --------

          -p or --prefix=WORD

            The prefix to use for the generated macro name. Default =
            BREEZE_GUARD_.

        Example:
        --------

        Assuming the tool is invoked with

          make_include_guard.py --prefix MY_PREFIX_

        then a possible output is:

                                         random part
                            |------------------------------|
          #ifndef MY_PREFIX_XcocANDF5GeFUffA3GTta5eUcluqZwhM
          #define MY_PREFIX_XcocANDF5GeFUffA3GTta5eUcluqZwhM
          <newline1><contents from standard input...><newline2>
          #endif

        Note:
            newline2 is omitted if no characters are available from
            standard input.
"""
# ----------------------------------------------------------------------------

import argparse
import random
import string
import sys

def _generate_random_part( length ):
    alphabet = string.ascii_letters + string.digits
    return "".join( random.SystemRandom().choice( alphabet )
            for i in range( length ) )


def _make_include_guard_name( prefix, random_part_length ):
    return prefix + _generate_random_part( random_part_length )


def _reject_reserved_identifiers( identifier ):
    if identifier.startswith( "_" ) or "__" in identifier:
        sys.exit( "Can't use a reserved name; please, change your prefix"
                  " (see [lex.name] in the C++ standard)" )


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument( "-p", "--prefix", help =
        "The prefix to use for the generated macro name."
        " A prefix which would make the macro name reserved is rejected.",
        default = "BREEZE_GUARD_" )

    arguments = parser.parse_args()

    _reject_reserved_identifiers( arguments.prefix )

    macro_name = _make_include_guard_name( arguments.prefix, 32 )

    print( "#ifndef " + macro_name )
    print( "#define " + macro_name )
    print()
    stdin_content = sys.stdin.read()
    if stdin_content != "":
        sys.stdout.write( stdin_content + "\n" )
    print( "#endif" )


main()
