// ===========================================================================
//                     Copyright 2006-2013 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A token concatenation macro.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_FQYU7dF1crCo42cp2n1PRVbw1ctMjDqe
#define BREATH_GUARD_FQYU7dF1crCo42cp2n1PRVbw1ctMjDqe

/*!
        A facility for concatenation of preprocessing tokens.

        Concatenates the two preprocessing tokens which end the
        argument x and start the argument y, respectively. The ##
        operator is used for that.

        Naming rationale:
        -----------------

        Though both the C and the C++ standard use the term
        "concatenate", and not "paste", with reference to what ## does,
        it was deemed that the name BREATH_CONCATENATE_TOKEN was a tad
        too long, especially considering that this macro is often
        invoked within other macro invocations. "Token pasting" is a
        well-established expression within the C and C++ communities.
        (A similar comment applies, obviously, to the _DELAYED
        variant.)
*/

#define BREATH_TOKEN_PASTE( x, y )  x ## y

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
