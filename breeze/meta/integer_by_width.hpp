// ===========================================================================
//                     Copyright 2006-2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Integer types of user-specified width.
//!
//!     As for their C99 counterparts, there's no guarantee that the
//!     types are provided for any given value of \c N.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_HdHZPdx1OyaeosOjcrni6ByNfUBalEG4
#define BREEZE_GUARD_HdHZPdx1OyaeosOjcrni6ByNfUBalEG4

#include "breeze/top_level_namespace.hpp"
#include "breeze/meta/select.hpp"
#include <limits>

namespace breeze_ns {
//!\cond implementation
namespace integer_by_width_private {

//      This could be elegantly implemented via type lists or maps, but
//      we chose to keep metaprogramming (and dependencies) to a
//      minimum.
// ---------------------------------------------------------------------------
template< typename IntType, int index > struct types ;

//      "list" of unsigned (list of signed not yet implemented [gps])
//
template<> struct types< unsigned, 0 > { typedef unsigned char    type ; } ;
template<> struct types< unsigned, 1 > { typedef unsigned short   type ; } ;
template<> struct types< unsigned, 2 > { typedef unsigned int     type ; } ;
template<> struct types< unsigned, 3 > { typedef unsigned long    type ; } ;
template<> struct types< unsigned, 4 > { typedef unsigned long long type ; } ;


template< int width,
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
//!\endcond

//      integer_by_width:
//      =================
//
//!     \brief
//!         Provides, if available, an integer type with width \c width.
//!
//!     Differently from \c intN_t in C99, it can have padding and,
//!     until C++20, can use a representation different from two's
//!     complement.
//!
//!     If a type with width \c width is not available, the program is
//!     ill-formed.
//!
//!     \par Type requirements
//!         \c T shall be either \c signed \c int or \c unsigned \c int.
// ---------------------------------------------------------------------------
template< int width, typename T /* gps temp = signed */ >
class integer_by_width
{
public:
    typedef typename integer_by_width_private
                         ::selector< width, T, 0 >::type type ;
} ;

//      unsigned_integer_by_width:
//      ==========================
//
//!     \brief
//!         A synonym of <code>integer_by_width< width, unsigned >
//!         </code>.
// ---------------------------------------------------------------------------
template< int width >
class unsigned_integer_by_width
    :   public integer_by_width< width, unsigned >
{
} ;

}

#endif
