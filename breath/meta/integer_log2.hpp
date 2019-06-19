// ===========================================================================
//                     Copyright 2003-2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Returns the integer part of the logarithm, to base 2, of
//!            its argument.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_4uQJExogJdntOgg4rVCN5jmuqREdR7xS
#define BREATH_GUARD_4uQJExogJdntOgg4rVCN5jmuqREdR7xS

namespace breath {
//! \cond
namespace  integer_log2_private {

//      choose_initial_n
//
//      Recursively doubles its integer argument n, until 2*n becomes
//      >= of the "width" (C99, 6.2.6.2p6) of integer_log2's
//      argument_type.
//
//      Used to get the maximum power of two smaller than the width.
//
//      Example: if on your platform integer_log2_argument_type has
//               48 value bits this yields n=32.
//
//      It's easy to prove that, starting from such a value of n the
//      core algorithm works correctly for any width of
//      integer_log2_argument_type and that recursion always
//      terminates with x = 1 and n = 0 (see the algorithm's
//      invariant).
// ---------------------------------------------------------------------------
typedef unsigned long long
                        argument_type ;
typedef int             result_type ;

template< result_type n >
struct choose_initial_n
{

    //      Note the repeated conversions to argument_type: we must
    //      convert at *each* shift, because the operands of << are
    //      promoted.
    // -----------------------------------------------------------------------
    static bool const
                c = argument_type(argument_type(
                                    argument_type(1) << n ) << n ) != 0
        ;
    static result_type const
                value = !c*n + choose_initial_n< 2*c*n >::value
        ;

} ;


template< result_type n >
bool const
choose_initial_n< n >::c ;

template< result_type n >
result_type const
choose_initial_n< n >::value ;

template<>
struct choose_initial_n< 0 >
{
    static result_type const value = 0 ;
} ;



//      Start computing from n_zero - must be a power of two.
// ---------------------------------------------------------------------------
const result_type n_zero = 4 ;
const result_type initial_n = choose_initial_n<n_zero>::value ;

//      integer_log2_impl<>
//
//      Invariant:
//                     2n
//      1 <= x && x < 2    at the start of each recursion
//                         (see also choose_initial_n)
//
//      Type requirements:
//
//      argument_type may be any unsigned type with at least n_zero + 1
//      value bits. (Note: If larger types will be standardized -e.g.
//      unsigned long long- then the argument_type typedef can be
//      changed without affecting the rest of the code.)
// ---------------------------------------------------------------------------
template< argument_type x, result_type n = initial_n >
struct integer_log2_impl
{

    enum { c = (x >> n) > 0 } ; // x >= 2**n ?
    static result_type const
                    value = c*n
                            + ( integer_log2_impl< ( x>>c*n ), n/2 >::value )
                    ;

} ;

template<>
struct integer_log2_impl< 1, 0 >
{
    static result_type const
                        value = 0 ;
} ;

template< argument_type arg, result_type res >
result_type const
integer_log2_impl< arg, res >::value ;

}
//! \endcond

namespace meta {

typedef integer_log2_private::argument_type
                    integer_log2_argument_type ;
typedef integer_log2_private::result_type
                    integer_log2_result_type ;

template< integer_log2_argument_type x >
class [[ deprecated( "consider using the constexpr"
                     " breath::integer_log2()" ) ]] integer_log2
{
public:
    static integer_log2_result_type const
         value = integer_log2_private::
                    integer_log2_impl< x >::value ;

} ;


template<>
class integer_log2< 0 >
{
} ;

template< integer_log2_argument_type x >
integer_log2_result_type const
integer_log2< x >::value ;

}
}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
