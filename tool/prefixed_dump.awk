#! /bin/awk -f
# ============================================================================
#                         Copyright 2008 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________
#
#       Arguments:
#       ==========
#
#       All arguments must be passed via awk's ENVIRON (for the
#       rationale, see our Scripting Guidelines). They are:
#
#       * alignment
#           One of 'align_right', 'align_center', 'align_left'  [gps]
#       * prefix
#           A string to be prefixed to every line of the input; can be
#           empty
#       * width
#           An integer > length( prefix ), giving the maximum length in
#           characters of the whole output line (including prefix)
#       * comment_pattern
#           An ERE. Input lines matching this regular expression are
#           considered "comments": they yield no corresponding output
# ----------------------------------------------------------------------------

function max( a, b )
{
    return a < b ? b : a
}

function centered( text, room )
{
    len =               length( text )
    pad = len > room ?  0                               \
                     :  int( ( room - len ) / 2 )

    return sprintf( "%*s", pad + len, text )
}

BEGIN {
    alignment =       ENVIRON[ "alignment" ]
    prefix =          ENVIRON[ "prefix" ]
    width =           ENVIRON[ "width" ]
    comment_pattern = ENVIRON[ "comment_pattern" ]
}

$0 ~ comment_pattern {
    next
}

length() == 0 {
    print prefix
    next
}

{
    printf( "%s ", prefix )

    room = width - length( prefix ) - 1
    text = substr( $0, 1, room ) # this may truncate

    if ( alignment == "align_center" ) {
        print centered( text, room )
    } else if ( alignment == "align_right" ) {
        # not implemented - gps
    } else {
        # align to left and be done with it
        print text
    }
}

# Local Variables:
# mode: awk
# indent-tabs-mode: nil
# c-basic-offset: 4
# End:
# vim: set ft=awk et sts=4 sw=4:
