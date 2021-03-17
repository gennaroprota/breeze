// ===========================================================================
//                     Copyright 2006-2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Typedefs for built-in integer types of user-specified
//!            width.
//!
//!     As for the various <code>std::[u]intN_t</code> from
//!     <code><cstdint></code>, there's no guarantee that the typedefs
//!     are provided for any given width.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_HdHZPdx1OyaeosOjcrni6ByNfUBalEG4
#define BREEZE_GUARD_HdHZPdx1OyaeosOjcrni6ByNfUBalEG4

#include "breeze/top_level_namespace.hpp"
#include "breeze/meta/select.hpp"
#include <limits>

namespace breeze_ns {
namespace meta {

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
//!         Provides, if possible, a typedef to a built-in integer type
//!         with width \c width.
//!
//!     If a (signed or unsigned, according to \c T) type with width \c
//!     width is available, a public member typedef \c type is provided
//!     that names that type; otherwise, the program is ill-formed.
//!
//!     Differently from <code>std::[u]intN_t</code>, the named type may
//!     have padding; until C++20, it may also use a representation
//!     different from two's complement (if it allows negative values at
//!     all).
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
//!         Equivalent to <code>integer_by_width< width, unsigned >
//!         </code>.
// ---------------------------------------------------------------------------
template< int width >
class unsigned_integer_by_width
    :   public integer_by_width< width, unsigned >
{
} ;

}
}

#endif
