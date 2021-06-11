# ============================================================================
#                      Copyright 2008-2021 Gennaro Prota
#
#                   Licensed under the 3-Clause BSD License.
#              (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
#               <https://opensource.org/licenses/BSD-3-Clause>.)
# ____________________________________________________________________________

from datetime import datetime

#       make_copyright_notice():
#       ========================
#
#       With the disclaimer that I'm not a lawyer and you shouldn't rely
#       on anything I'm going to say: this function returns a copyright
#       notice valid for all countries that are members of the Berne
#       Convention (1988).
#
#       For more information, see
#
#        - U.S. Copyright Office - Copyright Notice (Circular 3)
#          <https://www.copyright.gov/circs/circ03.pdf>
#
#        - U.S. Code, TITLE 17 > CHAPTER 4 > section 401
#
#       Note, among other things, that there's no "(c)" in it: it is
#       indeed unclear whether a court outside the U.S. would consider
#       that string as a legal "ASCII alternative" to the copyright
#       symbol.
#
#       Note, too, that---from Circular 3 linked to above---under the
#       "Universal Copyright Convention" (the UCC) only the copyright
#       symbol is acceptable in a copyright notice: the word "Copyright"
#       or the abbreviation are not acceptable. This would pose a
#       problem e.g. for C++ source files, because, regardless of font
#       and encoding issues, it may not be possible to use the copyright
#       symbol in them without invoking undefined behavior. I asked
#       Arnoud Engelfriet about this, who pointed out that:
#
#           "Yes, in a UCC member you cannot use the word or the
#           abbreviation *but* I'm not aware of any country that's
#           member of the UCC but not the Berne Convention"
#
#
#       What is not clear to me is what "country" is a work first
#       published in when it is actually first published on the
#       Internet. To this Arnoud Engelfriet replied:
#
#           "I don't think I've ever seen that addressed in court.
#           Most of the time it makes no difference, because under
#           Berne countries must give an alien the same rights as
#           their own citizens. If a US citizen infringes my
#           copyright, it doesn't matter where I first published the
#           work.
#
#           It could be relevant when the country of first
#           publication is not a Berne convention country. [...]
#
#           My guess is that courts would look at the site's
#           registration and ownership. Sourceforge is operated by a
#           US company, so that would probably count as a first
#           publication in the USA. But this is really speculative
#           as I've never seen this issue in a court anywhere."
# ----------------------------------------------------------------------------
def make_copyright_notice( copyright_owner ):
    """
    Returns a copyright notice for the current year.

    Keyword arguments:
        copyright_owner     A string to be used as the designation of
                            the copyright owner.

    See the comments to make_copyright_notice.py for more details.
    """
    return "Copyright {} {}".format( datetime.now().year, copyright_owner )
