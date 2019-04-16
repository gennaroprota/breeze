// ===========================================================================
//                     Copyright 2011-2013 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Max for subrange adaptation.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_Z7sZqZ1T5DzTJ6V6zdst2zbGcymbnLM7
#define BREATH_GUARD_Z7sZqZ1T5DzTJ6V6zdst2zbGcymbnLM7

namespace breath {

//      subrange_max():
//      ===============
//
//!     \return
//!         The maximum value that can be kept (before taking the
//!         remainder of the division by `x+1') for getting a random (or
//!         pseudorandom) integer in the range [0, x] from a source that
//!         spans [0, m], x <= m.
//!
//!     Typical example: wanting a value in [0, 5] (dice) from [0,
//!     RAND_MAX]; if e.g. RAND_MAX == 32767 then subrange_max(5,
//!     RAND_MAX) returns
//!
//!         32765
//!
//!     This allows discarding only a tiny fraction of the values in
//!     the whole range of the source (only the last two, in fact),
//!     rather than discarding anything greater than or equal to six.
//!
//!     Why that value? The idea, of course, is that there are 32766
//!     numbers in [0, 32765], and that is a multiple of six (the
//!     number of values in [0, 5]). So, the remainders 0, 1, 2, 3, 4
//!     and 5 all appear with the same probability (if the source is
//!     not biased). If we took the whole range then, of course, 0 and
//!     1 would be more frequent than the others.
//!
//!     With respect to just discarding anything greater than x:
//!
//!         For pseudorandom numbers this basically saves execution
//!         time.
//!         For true random numbers it avoids needlessly discarding
//!         numbers and thus consuming precious entropy.
//!
//!     \pre
//!         0 <= x <= m   (i.e. destination range not wider
//!                        than source one)
// -------------------------------------------------------------------------
unsigned long       subrange_max( unsigned long x, unsigned long m ) ;

}


#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
