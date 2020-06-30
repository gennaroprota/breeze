// ===========================================================================
//                        Copyright 2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A byte buffer to host an object of type \c T.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_ilYRG2ibsfCoQd4vz7X5Cik5Q8E0z1pO
#define BREATH_GUARD_ilYRG2ibsfCoQd4vz7X5Cik5Q8E0z1pO

#include "breath/top_level_namespace.hpp"
#include "breath/idiom/declare_non_copyable.hpp"
#include "breath/meta/select.hpp"
#include <cstddef>

namespace breath_ns {

//! \cond implementation
namespace aligned_storage_private {

template< typename T >
class align_of
{
    struct hack
    {
        char                c ;
        T                   t ;
    } ;

public:
    static std::size_t const
                        value = sizeof( hack ) - sizeof( T ) ;

private:
    //      Surrogates of static_asserts (which we don't use because we
    //      want this file to be usable in C++98/03).
    // -----------------------------------------------------------------------
    char                is_power_of_2[ value > 0 &&
                                     ( value & ( value-1 ) ) == 0 ] ;

    char                is_submultiple[ sizeof( T ) % value == 0 ] ;
} ;

template< typename T >
std::size_t const       align_of< T >::value ;


template< int index >
struct              pod_array ;

static int const    number_of_pod_types = 7 ;

template<> struct   pod_array< 0 > { typedef char        type ; } ;
template<> struct   pod_array< 1 > { typedef short       type ; } ;
template<> struct   pod_array< 2 > { typedef int         type ; } ;
template<> struct   pod_array< 3 > { typedef long        type ; } ;
template<> struct   pod_array< 4 > { typedef float       type ; } ;
template<> struct   pod_array< 5 > { typedef double      type ; } ;
template<> struct   pod_array< 6 > { typedef long double type ; } ;
template<> struct   pod_array< number_of_pod_types > {
                // if you get to instantiate this you'll have to add
                // more types to the array
} ;


template< typename T, int start_index >
class searcher
{
    typedef         typename pod_array< start_index >::type
                        candidate ;
public:
    typedef typename meta::select_<
        align_of< candidate >::value == align_of< T >::value,
        candidate,
        searcher< T, start_index + 1 >
    >::type
                        type ;
} ;

template< typename T >
struct pod_with_same_align
{
    typedef typename searcher< T, 0 >::type
                        type ;
} ;

}
//! \endcond

//      aligned_storage_for:
//      ====================
//
//!     An object that contains a byte buffer suitably sized and
//!     aligned for the type \c T.
//!
//!     Note that this has a different interface from TR1's or C++11's
//!     analogous: both of the latter take one or two numeric
//!     arguments (size and alignment); this one takes just a type
//!     (the type that we want the same alignment of). Among other
//!     things, the C++11 scheme allows for storing arrays:
//!
//!     <code>
//!         aligned_storage< n * sizeof( T ), alignof( T ) >
//!     </code>
//!
//!     What's more, C++11 has support for declaring an aligned buffer
//!     directly in core language:
//!
//!     <code>
//!         alignas( T ) unsigned char arr[ sizeof( T ) ] ;
//!     </code>
//!
//!     So: this facility exists basically for C++03; and all of the
//!     alternatives (this one, TR1's one and the library-based
//!     C++11's one) will be made superfluous by C++11's core support.
// ---------------------------------------------------------------------------
template< typename T >
class               aligned_storage_for ;

//!     "Empty" specialization to disable usage of the template for
//!     arrays.
// ---------------------------------------------------------------------------
template< typename T, std::size_t n >
class               aligned_storage_for< T[ n ] >
{
} ;

template< typename T >
class aligned_storage_for
{
public:
    //!     Copy constructor and copy-assignment operator deleted.
    // -----------------------------------------------------------------------
    BREATH_DECLARE_NON_COPYABLE( aligned_storage_for )

    //!     Constructs an uninitialized buffer.
    // -----------------------------------------------------------------------
                        aligned_storage_for() noexcept {}

    //!     \return
    //!         The address of the internal (aligned) buffer, as a
    //!         <code>void *</code>.
    // -----------------------------------------------------------------------
    void *              address() noexcept       { return m_raw_buffer ; }

    //!     \return
    //!         The address of the internal (aligned) buffer, as a
    //!         <code>void const *</code>.
    // -----------------------------------------------------------------------
    void const *        address() const noexcept { return m_raw_buffer ; }

private:
    union
    {
        unsigned char   m_raw_buffer[ sizeof( T ) ] ;
        typename aligned_storage_private::pod_with_same_align< T >::type
                        dummy_for_alignment ;
    } ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
