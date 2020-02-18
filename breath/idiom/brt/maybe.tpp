// ===========================================================================
//                     Copyright 2006-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/diagnostics/assert.hpp"
#include <new>
#include <utility>

namespace breath {

template< typename T, typename Traits >
maybe< T, Traits >::maybe( status_type status ) noexcept
    :   m_status( status ) // gps use std::move()?
{
    BREATH_ASSERT( ! Traits::is_valid( status ) ) ;
}

template< typename T, typename Traits >
maybe< T, Traits >::maybe( T const & value, status_type status )
    :   m_status( status ) // gps use std::move()?
{
    BREATH_ASSERT( Traits::is_valid( status ) ) ;

    construct( value ) ;
}

template< typename T, typename Traits >
maybe< T, Traits >::maybe( T && value, status_type status ) noexcept
    :   m_status( status ) // gps use std::move()?
{
    BREATH_ASSERT( Traits::is_valid( status ) ) ;

    construct( std::move( value ) ) ;
}

template< typename T, typename Traits >
maybe< T, Traits >::maybe( maybe const & other )
    //      Caution: don't move other.status(), because this would leave
    //      it in an unspecified state, possibly inconsistent with the
    //      actual status of other (e.g. it could change other.status()
    //      into an invalid status although other *has* a value).
    // -----------------------------------------------------------------------
    :   m_status( other.status() )
{
    if ( other.is_valid() ) {
        construct( other.value() ) ;
    }
}

template< typename T, typename Traits >
maybe< T, Traits >::maybe( maybe && other ) noexcept
    //      Caution: see the comment to the copy constructor
    :   m_status( other.status() )
{
    if ( other.is_valid() ) {
        construct( std::move( other.non_const_value() ) ) ;
    }
}

template< typename T, typename Traits >
maybe< T, Traits >::~maybe() noexcept
{
    if ( is_valid() ) {
        destroy() ;
    }
}

template< typename T, typename Traits >
maybe< T, Traits > &
maybe< T, Traits >::operator =( maybe const & other )
{
    if ( other.is_valid() ) {
        if ( is_valid() ) {
            *static_cast< T * >( m_storage.address() ) = other.value() ;
        } else {
            construct( other.value() ) ;
        }
    } else if ( is_valid() ) {
        destroy() ;
    }

    m_status = other.status() ;
    return *this ;
}

template< typename T, typename Traits >
maybe< T, Traits > &
maybe< T, Traits >::operator =( maybe && other ) noexcept
{
    if ( other.is_valid() ) {
        if ( is_valid() ) {
            *static_cast< T * >( m_storage.address() )
                                       = std::move( other.non_const_value() ) ;
        } else {
            construct( std::move( other.non_const_value() ) ) ;
        }
    } else if ( is_valid() ) {
        destroy() ;
    }

    //      Caution: see the corresponding comment in the move
    //      constructor.
    // -----------------------------------------------------------------------
    m_status = other.m_status ;

    return *this ;
}

//      Note that T's assignment operator exception guarantee reflects
//      that of this operator =().
// ---------------------------------------------------------------------------
template< typename T, typename Traits >
maybe< T, Traits > &
maybe< T, Traits >::operator =( T const & value )
{
    if ( is_valid() ) {
        *static_cast< T * >( m_storage.address() ) = value ;
    } else {
        construct( value ) ;
    }
    m_status = Traits::default_valid() ; // gps use std::move()?
    return *this ;
}

template< typename T, typename Traits >
maybe< T, Traits > &
maybe< T, Traits >::operator =( T && value ) noexcept
{
    if ( is_valid() ) {
        *static_cast< T * >( m_storage.address() ) = std::move( value ) ;
    } else {
        construct( std::move( value ) ) ;
    }
    m_status = Traits::default_valid() ; // gps use std::move()?
    return *this ;
}

template< typename T, typename Traits >
typename maybe< T, Traits >::status_type
maybe< T, Traits >::status() const noexcept
{
    return m_status ;
}

template< typename T, typename Traits >
bool
maybe< T, Traits >::is_valid() const noexcept
{
    return Traits::is_valid( status() ) ;
}

template< typename T, typename Traits >
T const &
maybe< T, Traits >::value() const noexcept
{
    BREATH_ASSERT( is_valid() ) ;
    return *static_cast< T const * >( m_storage.address() ) ;
}

template< typename T, typename Traits >
T
maybe< T, Traits >::default_to( T const & default_value ) const
{
    return is_valid()
        ? value()
        : default_value ;
}

template< typename T, typename Traits >
void
maybe< T, Traits >::construct( T const & value )
{
    new( m_storage.address() ) T( value ) ; // may throw
}

template< typename T, typename Traits >
void
maybe< T, Traits >::construct( T && value ) noexcept
{
    new( m_storage.address() ) T( std::move( value ) ) ;
}

template< typename T, typename Traits >
void
maybe< T, Traits >::destroy() noexcept
{
    BREATH_ASSERT( is_valid() ) ;
    static_cast< T * >( m_storage.address() )->T::~T() ;
}

template< typename T, typename Traits >
T &
maybe< T, Traits >::non_const_value() noexcept
{
    BREATH_ASSERT( is_valid() ) ;
    return *static_cast< T * >( m_storage.address() ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
