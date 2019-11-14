// ===========================================================================
//                     Copyright 2006-2011 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A generalized version of \c std::accumulate().
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_AIxamIWyjxqb3pPGHU23CYP8v7Zo1TTt
#define BREATH_GUARD_AIxamIWyjxqb3pPGHU23CYP8v7Zo1TTt

namespace breath {

//      accumulate_traits:
//      ==================
//
//!     Traits template for \c breath::accumulate().
//!     (gps should we use the term "policy" in place of "traits"?)
// ---------------------------------------------------------------------------
template< typename T >
class accumulate_traits
{
public:
    //!     The type of the default init value for \c
    //!     breath::accumulate().
    // -----------------------------------------------------------------------
    typedef T           init_type ;

    //!     The type of the result of \c breath::accumulate().
    // -----------------------------------------------------------------------
    typedef T           result_type ;

    //!     \return
    //!         The default init value for \c breath::accumulate().
    // -----------------------------------------------------------------------
    static init_type    first() ;

    //!     Performs a summation of the elements in the range <code>
    //!     [begin, end)</code> via <code>operator +=()</code> (which is
    //!     searched via ADL). Can have a different implementation in
    //!     a user specialization.
    // -----------------------------------------------------------------------
    template< typename It >
    static result_type  compute( It begin, It end, init_type & value ) ;
} ;

//      accumulate():
//      =============
//!
//!     Traits
//!     ------
//!
//!     \c breath::accumulate() uses \c accumulate_traits as a point of
//!     customization: you are allowed to specialize it, in namespace
//!     \c breath, for your own types.
//!
//!     See \c accumulate_traits for the behavior of the unspecialized
//!     traits template.
//!
//!     Any \c accumulate_traits shall provide the following
//!     accessible members:
//!
//!      - init_type
//!      - result_type
//!      - first()
//!      - compute()
// ---------------------------------------------------------------------------
template< typename InputIterator, typename T >
typename accumulate_traits< T >::result_type
accumulate( InputIterator begin,
            InputIterator end,
            T v = accumulate_traits< T >::first() ) ;

}

#include "brt/accumulate.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
