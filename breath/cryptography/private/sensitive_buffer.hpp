// ===========================================================================
//                     Copyright 2007-2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief  A buffer for sensitive data.
// -------------------------------------------------------------------------

#ifndef BREATH_GUARD_cYIOKCI73iMumaonvDavBYvSD0UPrlq4
#define BREATH_GUARD_cYIOKCI73iMumaonvDavBYvSD0UPrlq4

#include <cstddef>

namespace breath {

//      This template is a quick hack to be replaced with a more
//      complete solution.
// -------------------------------------------------------------------------
template< typename T >
class sensitive_buffer ;

template< typename T, std::size_t n >
class sensitive_buffer< T[ n ] >
{
    T m_data[ n ] ;

public:
    typedef std::size_t size_type ;
    typedef       T &   reference ;
    typedef T const &   const_reference ;
    typedef       T *   iterator ;
    typedef T const *   const_iterator ;

                        sensitive_buffer() ;

    template< typename InputIter >
                        sensitive_buffer( InputIter begin, InputIter end ) ;

    explicit            sensitive_buffer( T const ( &src )[ n ] ) ;

                        ~sensitive_buffer() noexcept ;

    // iteration and access
    iterator            begin() noexcept ;
    iterator            end() noexcept ;

    const_iterator      begin() const noexcept ;
    const_iterator      end()   const noexcept ;

    reference           operator []( size_type index ) ;
    const_reference     operator []( size_type index ) const ;

private:
    void                wipe() noexcept ;
} ;

}

#include "sensitive_buffer.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
