// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/diagnostics/check_type_completeness.hpp"
#include <utility>

namespace breath_ns {

template< typename T >
auto_array< T >::auto_array() noexcept
    :   m_ptr( nullptr )
{
}

template< typename T >
auto_array< T >::auto_array( T * p ) noexcept
    :   m_ptr( p )
{
}

template< typename T >
auto_array< T >::auto_array( auto_array && other ) noexcept
    :   m_ptr( other.m_ptr )
{
    other.m_ptr = nullptr ;
}

template< typename T >
auto_array< T >::~auto_array() noexcept
{
    do_delete() ;
}

template< typename T >
auto_array< T > &
auto_array< T >::operator =( auto_array && rhs ) noexcept
{
    std::swap( m_ptr, rhs.m_ptr ) ;
    return *this ;
}

template< typename T >
T *
auto_array< T >::get() noexcept
{
    return m_ptr ;
}

template< typename T >
T const *
auto_array< T >::get() const noexcept
{
    return m_ptr ;
}

template< typename T >
void
auto_array< T >::reset( T * p ) noexcept
{
    if ( p == m_ptr ) {
        return ;
    }

    do_delete() ;
    m_ptr = p ;
}

template< typename T >
void
auto_array< T >::do_delete() noexcept
{
    check_type_completeness< T >() ;
    delete [] m_ptr ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
