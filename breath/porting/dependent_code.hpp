// ===========================================================================
//                     Copyright 2008-2013 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief This file is for internal use only.
//
//      This is the file which is internally included every time we need
//      to select code according to one or more of the configuration
//      variables (system, compiler, etc.). Note that it only relies on
//      the preprocessing facilities, which, in turn, don't need any
//      configuration.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_LJrbr2rF89IS3w34IDEgr8K9ZUsCl9Ll
#define BREATH_GUARD_LJrbr2rF89IS3w34IDEgr8K9ZUsCl9Ll

#include "breath/preprocessing/paste.hpp"
#include "breath/preprocessing/stringize_after_expansion.hpp"

//      Dependent #includes:
//      ====================
//
//      The macros below create a narrow string-literal for use in a
//      #include directive:
//
//          #include BREATH_DEPENDENT_CODE( compiler, file.hpp )
//
//      Since string-literals and header-names are different kinds of
//      tokens, it's natural to ask: is that safe?
//
//      Here are some notes about why we think it is.
//
//      First off, at the time preprocessing directives, such as
//      #include, are executed (phase 4 of translation) preprocessing
//      tokens have, conceptually, already been formed. And
//      header-names are only formed within a #include. So, how does
//      the compiler handle something like
//
//          #define NAME "my_file.h"
//          #include NAME
//
//      ? The C standard has an example of the above since its C90
//      version, and makes it very clear that the intent is for it to
//      "just work".
//
//      Of course "my_file.h" is tokenized as a string-literal in
//      phase 3. The #include has thus the form
//
//              # include pp-tokens new-line
//
//      mentioned in C99, 6.10.2 p4:
//
//      <quote>
//          A preprocessing directive of the form [above] (that does
//      not match one of the two previous forms) is permitted. The
//      preprocessing tokens after include in the directive are
//      processed just as in normal text. (Each identifier currently
//      defined as a macro name is replaced by its replacement list of
//      preprocessing tokens.) The directive resulting after all
//      replacements shall match one of the two previous forms.
//      </quote>
//
//      The key portions here are "processed just as in normal text"
//      and "shall match one of the two previous forms". The
//      aforementioned two previous forms are
//
//      # include <h-char-sequence> new-line        (1)
//
//      and
//
//      # include "q-char-sequence" new-line        (2)
//
//      N.B.: char-sequences appear, not header-names. So, the only
//      reasonable interpretation of the standard seems to be that,
//      after the existing string-literal is substituted for the
//      invocation of the macro NAME, it is seen as "q-char-sequence"
//
//          {#}{include}{"}{my_file.h}{"}
//                          ^-------^
//                       q-char-sequence
//
//      ignoring its previous tokenization as a string-literal
//      ("normal text"). Note, too, that in general the previous
//      tokenization can't be completely ignored either, because the
//      compiler will collect the characters differently in a string
//      literal, due to support of escape sequences and UCNs: e.g.
//      "a\b" will be parsed as having two non-null characters (an 'a'
//      and a backspace), and "\U00000026" as having one non-null
//      character (an ampersand). At the point that any of them might
//      be substituted in the #include they would still have the same
//      number of characters, of course. However, as long as after
//      replacement of trigraphs none of
//
//        (a)  \            [the only way to begin an escape sequence
//                           or a UCN]
//        (b)  ', //, /*
//        (c)  "
//
//      appears in the *spelling* of the literal there can be no
//      different way to collect the characters, and (the behavior is
//      well-defined and) the string-literal can be correctly seen as
//      matching form (2).
//      [NOTE:
//      - in C++03, all of (a), (b) and (c) lead to UB in a
//        #include ""
//      - in the Final Committee Draft for C++0x, all of (a), (b) and
//        (c) are specified as conditionally supported with
//        implementation-defined semantics
//
//        (about the quote character there seems to be a defect in
//        both documents (not present in C99), because a q-char cannot
//        be a quote anyway... Fortunately this isn't going to affect
//        any of us, really, and I'll ignore this quote character
//        non-issue in all that follows)]
//
//      A simple way to ensure all of the above, trigraphs issues
//      included, is to prohibit all of \, ', //, /* and ? (question
//      mark --all trigraphs have two of them). Which, of course, is
//      nowhere near to being a real limitation :-)
//
//      Note, finally, that the above is a simplified variation of
//      what we do here, used to make the issue clearer to
//      follow. What we actually do is forming our "my_file.h" via the
//      stringizing operator. The standard has an example of this,
//      too, which we reproduce below:
//
//      #define str(s) # s
//      #define xstr(s) str(s)
//
//      #define INCFILE(n) vers ## n
//
//      #include xstr(INCFILE(2).h)
//
//      results in
//
//      #include "vers2.h"              (after macro replacement,
//                                       before file access)
//
//      Though examples are non-normative we believe that's a clear
//      confirmation that we correctly interpreted the intent, as
//      described above; the more so, considering that the same
//      example exists in C90, C99, C++98, C++03 and C++0x.
// ---------------------------------------------------------------------------

#define BREATH_DEPENDENT_CODE( variant, file_name )                           \
    BREATH_PASTE( BREATH_DEPENDENT_CODE_, variant )( file_name )           /**/


#define BREATH_DEPENDENT_CODE_compiler( file_name )                           \
    BREATH_STRINGIZE_AFTER_EXPANSION( dep/comp/BREATH_COMPILER/file_name ) /**/

#define BREATH_DEPENDENT_CODE_system( file_name )                             \
    BREATH_STRINGIZE_AFTER_EXPANSION( dep/syst/BREATH_SYSTEM/file_name )   /**/


#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
