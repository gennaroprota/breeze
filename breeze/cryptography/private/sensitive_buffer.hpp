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
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_cYIOKCI73iMumaonvDavBYvSD0UPrlq4
#define BREEZE_GUARD_cYIOKCI73iMumaonvDavBYvSD0UPrlq4

#include "breeze/top_level_namespace.hpp"
#include <cstddef>

namespace breeze_ns {

//      This template is a quick hack to be replaced with a more
//      complete solution.
// ---------------------------------------------------------------------------
template< typename T >
class sensitive_buffer ;

template< typename T, std::ptrdiff_t n >
class sensitive_buffer< T[ n ] >
{
    T                   m_data[ n ] ;

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

    reference           operator []( std::ptrdiff_t index ) ;
    const_reference     operator []( std::ptrdiff_t index ) const ;

private:
    void                wipe() noexcept ;
} ;

}

#include "sensitive_buffer.tpp"
#endif
