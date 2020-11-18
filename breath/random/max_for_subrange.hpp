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
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_Z7sZqZ1T5DzTJ6V6zdst2zbGcymbnLM7
#define BREATH_GUARD_Z7sZqZ1T5DzTJ6V6zdst2zbGcymbnLM7

#include "breath/top_level_namespace.hpp"

namespace breath_ns {

//      max_for_subrange():
//      ===================
//
//!     \return
//!         The maximum value that can be kept (before taking the
//!         remainder of the division by <tt>x + 1</tt>) for getting a
//!         random (or pseudorandom) integer in the range <tt>[0, x]
//!         </tt> from a source that spans <tt>[0, m]</tt>, <tt>x <= m
//!         </tt>.
//!
//!     Typical example: wanting a value in <tt>[0, 5]</tt> (dice) from
//!     <tt>[0, RAND_MAX]</tt>; if e.g. <tt>RAND_MAX == 32767</tt> then
//!     <tt>max_for_subrange(5, RAND_MAX)</tt> returns
//!
//!         <tt>32765</tt>
//!
//!     This allows discarding only a tiny fraction of the values in the
//!     whole range of the source (only the last two, in fact), rather
//!     than discarding anything greater than or equal to six.
//!
//!     Why that value? The idea, of course, is that there are <tt>32766
//!     </tt>numbers in <tt>[0, 32765]</tt>, and that is a multiple of
//!     six (the number of values in <tt>[0, 5]</tt>). So, the
//!     remainders <tt>0</tt>, <tt>1</tt>, <tt>2</tt>, <tt>3</tt>, <tt>4
//!     </tt> and <tt>5</tt> all appear with the same probability (if
//!     the source is not biased). If we took the whole range then, of
//!     course, <tt>0</tt> and <tt>1</tt> would be more frequent than
//!     the others.
//!
//!     With respect to just discarding anything greater than <tt>x
//!     </tt>:
//!
//!      - For pseudorandom numbers this basically saves execution time.
//!
//!      - For true random numbers it avoids needlessly discarding
//!        numbers and thus consuming precious entropy.
//!
//!     \pre
//!         0 <= x <= m   (i.e. destination range not wider
//!                        than source one)
// ---------------------------------------------------------------------------
unsigned long       max_for_subrange( unsigned long x, unsigned long m ) ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
