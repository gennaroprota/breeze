// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/diagnostics/require_type_completeness.hpp"
#include <utility>

namespace breeze_ns {

template< typename T >
array_pointer< T >::array_pointer() noexcept
    :   m_ptr( nullptr )
{
}

template< typename T >
array_pointer< T >::array_pointer( T * p ) noexcept
    :   m_ptr( p )
{
}

template< typename T >
array_pointer< T >::array_pointer( array_pointer && other ) noexcept
    :   m_ptr( other.m_ptr )
{
    other.m_ptr = nullptr ;
}

template< typename T >
array_pointer< T >::~array_pointer() noexcept
{
    do_delete() ;
}

template< typename T >
array_pointer< T > &
array_pointer< T >::operator =( array_pointer && rhs ) noexcept
{
    std::swap( m_ptr, rhs.m_ptr ) ;
    return *this ;
}

template< typename T >
T *
array_pointer< T >::raw_pointer() const noexcept
{
    return m_ptr ;
}

template< typename T >
void
array_pointer< T >::reset( T * p ) noexcept
{
    if ( p == m_ptr ) {
        return ;
    }

    do_delete() ;
    m_ptr = p ;
}

template< typename T >
void
array_pointer< T >::do_delete() noexcept
{
    require_type_completeness< T >() ;
    delete [] m_ptr ;
}

}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
