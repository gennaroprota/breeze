#! /bin/sh --
# ============================================================================
#                         Copyright 2009 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________

set -eu

.   "$BREEZE_ROOT/tool/shell/here_document.shc"

: <<eof1; : <<eof2
Hello,
eof1
World!
eof2


dump_here_document 'eof1'
