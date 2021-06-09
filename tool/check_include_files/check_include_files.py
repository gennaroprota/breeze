#! /usr/bin/env python3
# ============================================================================
#                         Copyright 2021 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________

"""
        Checks our include files.

        This script checks for mishaps in our include files.
        Specifically, that every .hpp file other than
        breeze/top_level_namespace.hpp that opens namespace breeze_ns
        includes breeze/top_level_namespace.hpp in its first include
        directive, that every .hpp file has one include guard (and only
        one), and that the names of the guarding macros are all
        distinct.

        It is tailored to our coding style, and is particularly simple,
        given that we don't use conditional compilation for anything
        else than include guards.
"""
# ----------------------------------------------------------------------------

import collections
import os
import re
import sys

argc = len( sys.argv )
if ( argc != 2 ):
    sys.exit( "Usage: check_include_files.py <root_dir_path>" )

root = sys.argv[ 1 ]
if ( not os.path.isdir( root ) ):
    sys.exit( "The specified directory was not found" )

regex                 = re.compile( "^#ifndef (BREEZE_GUARD_\w+)" )
macro_dict            = collections.defaultdict( list )
guard_counts          = collections.defaultdict( int )
opens_namespace       = collections.defaultdict( bool )
has_namespace_include = collections.defaultdict( bool )

exit_code  = 0
exit_error = 2
try:
    for dir_path, subdir_name, file_names in os.walk( root ):
        for name in file_names:
            if name.endswith( ".hpp" ):
                full_name = os.path.join( dir_path, name )
                guard_counts[ full_name ] = 0
                first_include_seen = False
                opens_namespace[ full_name ] = False
                has_namespace_include[ full_name ] = False
                for line in open( full_name ):
                    if line.find( "namespace breeze_ns" ) == 0:
                        opens_namespace[ full_name ] = True

                    if not first_include_seen and line.find( "#include" ) == 0:
                        first_include_seen = True

                        if line.find( '#include "breeze/top_level_namespace.hpp"') == 0:
                            has_namespace_include[ full_name ] = True

                    m = regex.match( line )
                    if m:
                        guard_counts[ full_name ] += 1
                        macro_name = m.group( 1 )
                        macro_dict[ macro_name ].append( full_name )
except Exception as ex:
    print( "An exception occurred: {}".format( ex ), file = sys.stderr )
    exit_code = exit_error

for file_name in opens_namespace:
    if os.path.basename( file_name) != "top_level_namespace.hpp"    \
            and opens_namespace[ file_name ]                        \
            and not has_namespace_include[ file_name ]:
        print( "Error: {} doesn't include top_level_namespace.hpp,"
               " or includes it after other files".format( file_name ),
               file = sys.stderr )

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
