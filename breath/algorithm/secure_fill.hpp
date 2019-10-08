// ===========================================================================
//                     Copyright 2006-2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A security-aware fill algorithm.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_orbeymgqIeZsonBH4PuD1mZImaMGlaZ1
#define BREATH_GUARD_orbeymgqIeZsonBH4PuD1mZImaMGlaZ1

#include "breath/idiom/volatilize.hpp"
#include <cstddef>

namespace breath {


//      secure_fill():
//      ==============
//
//!     This is completely analogous to the \c std::fill() algorithm,
//!     except that, due to a \c volatile qualification, it guarantees
//!     that the sequence is written to, even if it is never touched
//!     after the \c secure_fill() call (in other words: it ensures that
//!     the compiler will not optimize the function out); useful to
//!     zeroize passwords and other sensitive data.
//!
//!     Note that a convenience overload for built-in arrays is
//!     provided. For technical reasons, this overload is guaranteed to
//!     work for arrays of built-in types only.
//!
//!     Many thanks go to David R Tribble and Douglas A. Gwyn who
//!     clarified my doubts on comp.std.c; see the thread starting with
//!
//!       message-id: <38i6r2d5uksv7eovk0os7506k9bbshgl2j@4ax.com>
//!
//!     Note that, finally (!), the C++17 standard talks about "accesses
//!     through volatile glvalues" [intro.execution] instead of "access
//!     to volatile objects".
// ---------------------------------------------------------------------------
//      Note how this is intentionally implemented with a hand-coded
//      loop. It's not crystal clear whether we could use std::fill()
//      or std::fill_n() (which would bring the advantage of debug
//      mode and everything the underlying standard library
//      implementation might provide). On a relaxed reading of the
//      standard, it seems that, for instance
//
//        std::fill( arr, arr + n, value ) ;
//
//      should work as expected, since we pass regular pointers as
//      iterators and std::iterator_traits< T * >::value is required
//      to be T, which in our case is volatile qualified. It all
//      depends, however, on how the expression "assigns 'value'
//      through all the iterators in the range [first, last)", in
//      [alg.fill], is to be interpreted. Does it allow anything
//      different from the obvious *first = value, *first ++ = value
//      and similar?
// ---------------------------------------------------------------------------
template< typename T, std::size_t n >
void
secure_fill( T volatile ( &arr )[ n ], T const & value = T() )
{
    for ( std::size_t i = 0 ; i < n ; ++ i ) {
        arr[ i ] = value ;
    }
}

//      secure_fill():
//      ==============
//
//!     Version for sequences.
// ---------------------------------------------------------------------------
//
//      [FUTURE], [C++11] [gps]:
//      As a result of core issue 226, C++11 is likely to allow
//      default template arguments for function templates; so one day
//      we can change this to
//
//        template< typename ForwardIterator, typename T
//             = std::iterator_traits< ForwardIterator >::value_type
//        >
//        void secure_fill( ForwardIterator begin, ForwardIterator end,
//                          T const & value = T() )
// ---------------------------------------------------------------------------
template< typename ForwardIterator, typename T >
void
secure_fill( ForwardIterator begin, ForwardIterator end, T const & value )
{
    for ( ; begin != end ; ++ begin ) {
        breath::volatilize( *begin ) = value ;
    }
}

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
