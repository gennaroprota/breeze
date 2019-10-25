// ===========================================================================
//                     Copyright 2007-2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/algorithm/secure_fill.hpp"
#include "breath/diagnostics/assert.hpp"
#include <algorithm>

namespace breath {

template< typename T, std::size_t n >
void
sensitive_buffer< T[ n ] >::wipe() noexcept
{
    breath::secure_fill( m_data ) ;
}

template< typename T, std::size_t n >
sensitive_buffer< T[ n ] >::sensitive_buffer()
{
    // Calling secure_fill() might cause too much performance loss; and
    // then we are not supposed to cleanup data left over by others.
    // But until measurement...
    wipe() ;
}

template< typename T, std::size_t n >
template< typename InputIter >
sensitive_buffer< T[ n ] >::sensitive_buffer( InputIter begin,
                                              InputIter end )
{
    std::copy( begin, end, this->begin() ) ;
}

template< typename T, std::size_t n >
sensitive_buffer< T[ n ] >::sensitive_buffer( T const ( &src )[ n ] )
{
    std::copy( src, src + n, this->begin() ) ;
}

template< typename T, std::size_t n >
sensitive_buffer< T[ n ] >::~sensitive_buffer() noexcept
{
    wipe() ;
}

template< typename T, std::size_t n >
typename sensitive_buffer< T[ n ] >::iterator
sensitive_buffer< T[ n ] >::begin() noexcept
{
    return m_data ;
}

template< typename T, std::size_t n >
typename sensitive_buffer< T[ n ] >::iterator
sensitive_buffer< T[ n ] >::end() noexcept
{
    return m_data + n ;
}

template< typename T, std::size_t n >
typename sensitive_buffer< T[ n ] >::const_iterator
sensitive_buffer< T[ n ] >::begin() const noexcept
{
    return m_data ;
}

template< typename T, std::size_t n >
typename sensitive_buffer< T[ n ] >::const_iterator
sensitive_buffer< T[ n ] >::end() const noexcept
{
    return m_data + n ;
}

template< typename T, std::size_t n >
typename sensitive_buffer< T[ n ] >::reference
sensitive_buffer< T[ n ] >::operator []( std::ptrdiff_t index )
{
    BREATH_ASSERT( index >= 0 ) ;
    return m_data[ index ] ;
}

template< typename T, std::size_t n >
typename sensitive_buffer< T[ n ] >::const_reference
sensitive_buffer< T[ n ] >::operator []( std::ptrdiff_t index ) const
{
    BREATH_ASSERT( index >= 0 ) ;
    return m_data[ index ] ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
