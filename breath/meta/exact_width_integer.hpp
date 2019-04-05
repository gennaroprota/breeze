// =========================================================================
//                    Copyright 2006-2008 Gennaro Prota
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________
//
//!     \file
//!     \brief Templatized exact-width integer types.
//!
//!     As for their C99 counterparts, there's no guarantee that the
//!     types are provided for any given value of \c N.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_HdHZPdx1OyaeosOjcrni6ByNfUBalEG4
#define BREATH_GUARD_HdHZPdx1OyaeosOjcrni6ByNfUBalEG4

#include "breath/meta/select.hpp"
#include <limits>
#include <cstddef>

namespace breath {
//! \cond
namespace exact_width_integer_private {

//      This might be elegantly implemented via type lists or maps, but
//      we chose to keep metaprogramming (and dependencies) to a
//      minimum.
// -------------------------------------------------------------------------
template< typename IntType, int index > struct types ;

//      "list" of unsigned (list of signed not yet implemented [gps])
//
template<> struct types< unsigned, 0 > { typedef unsigned char    type ; } ;
template<> struct types< unsigned, 1 > { typedef unsigned short   type ; } ;
template<> struct types< unsigned, 2 > { typedef unsigned int     type ; } ;
template<> struct types< unsigned, 3 > { typedef unsigned long    type ; } ;
template<> struct types< unsigned, 4 > { typedef unsigned long long type ; } ;


template< std::size_t width,
          typename IntType,
          int n >
class selector
{
    typedef types< IntType, n > candidate ;
    enum { found =
        std::numeric_limits< typename candidate::type >::digits == width } ;

public:
    typedef typename meta::select_< found,
                                    candidate,
                                    selector< width, IntType, 1 + n >
                                  >::type s ;

    typedef typename s::type type ;
} ;

}
//! \endcond

//!     Provides an integer type with width \c width. Differently from
//!     \c intN_t in C99, it can have padding and can use a
//!     representation different from two's complement.
//!
//!     \par Type requirements
//!         \p T shall be either \c signed \c int or \c unsigned \c int.
// -------------------------------------------------------------------------
template< std::size_t width, typename T /* gps temp = signed */ >
class exact_width_integer
{
public:
    typedef typename exact_width_integer_private
                         ::selector< width, T, 0 >::type type ;
} ;

//!
//!     A synonym of <code>exact_width_integer< N, unsigned ></code>.
// -------------------------------------------------------------------------
template< std::size_t width >
class exact_width_unsigned_integer
    :   public exact_width_integer< width, unsigned >
{
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
