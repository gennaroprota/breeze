#! /usr/bin/env python3
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
# ----------------------------------------------------------------------------

import collections
import os
import re
import sys

argc = len( sys.argv )
if ( argc > 2 ):
    sys.exit( "Usage: check_include_guards.py [root_dir_path]" )

root = "../.." if argc == 1 else sys.argv[ 1 ]
if ( not os.path.isdir( root ) ):
    sys.exit( "The specified directory was not found" )

regex        = re.compile( "^#ifndef (BREEZE_GUARD_\w+)" )
macro_dict   = collections.defaultdict( list )
guard_counts = collections.defaultdict( int )

exit_code  = 0
exit_error = 2
try:
    for dir_path, subdir_name, file_names in os.walk( root ):
        for name in file_names:
            if name.endswith( ".hpp" ):
                full_name = os.path.join( dir_path, name )
                guard_counts[ full_name ] = 0
                for line in open( full_name ).readlines():
                    m = regex.match( line )
                    if m:
                        guard_counts[ full_name ] += 1
                        macro_name = m.group( 1 )
                        macro_dict[ macro_name ].append( full_name )
except Exception as ex:
    sys.stderr.write( "An exception occurred: {}\n".format( ex ) )
    exit_code = exit_error


for file_name in guard_counts:
    if guard_counts[ file_name ] != 1:
        print( "Error: {} Breeze guards in {}".format(
            guard_counts[ file_name ], file_name ) )
        exit_code = exit_error

for macro_name in macro_dict:
    if len( macro_dict[ macro_name ] ) != 1 :
        print( "Error: macro name {} duplicated in:".format( macro_name ) )
        for f in macro_dict[ macro_name ]:
            print( "    {}".format( f ) )
        exit_code = exit_error

exit( exit_code )
