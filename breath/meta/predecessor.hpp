// =========================================================================
//                       Copyright 2006 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief Metafunction yielding the predecessor of a type.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_UdGvvEgZV1WGbMzbsiKOg7UnnY910Qsa
#define BREATH_GUARD_UdGvvEgZV1WGbMzbsiKOg7UnnY910Qsa

namespace breath {
namespace meta {

//!     A meta::constant with the same \c value_type as \c T and \c
//!     value equal to <code>T::value - 1</code>.
// ---------------------------------------------------------------------------
template< typename T >
class predecessor
    :   public constant<
                        typename T::value_type
                        ,        T::value - 1
                       >
{
} ;

}
}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
