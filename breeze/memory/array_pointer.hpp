// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A smart pointer to an array object.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_FvaoTt7c3pTltKsed1Av5CAvE3SvnVIn
#define BREEZE_GUARD_FvaoTt7c3pTltKsed1Av5CAvE3SvnVIn

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//      array_pointer:
//      ==============
//
//!     \copybrief array_pointer.hpp
//!
//!     A smart pointer that retains sole ownership of an array through
//!     a pointer. An <code>array_pointer< T ></code> is similar to a
//!     <code>unique_ptr< T[], std::default_delete< T[] > ></code> but
//!     this template was written way before C++11.
//!
//!     Like for \c unique_ptr, instances of this template satisfy the
//!     requirements of <tt>MoveConstructible</tt> and <tt>
//!     MoveAssignable</tt>, but not the requirements of either <tt>
//!     CopyConstructible</tt> or <tt>CopyAssignable</tt>.
// ---------------------------------------------------------------------------
template< typename T >
class array_pointer
{
public:
    //!     Deleted copy constructor.
    // -----------------------------------------------------------------------
                        array_pointer( array_pointer const & ) = delete ;

    //!     Deleted copy assignment operator.
    // -----------------------------------------------------------------------
    array_pointer &     operator =( array_pointer const & ) = delete ;

                        array_pointer() noexcept ;
    explicit            array_pointer( T * ) noexcept ;
                        array_pointer( array_pointer && ) noexcept ;
                        ~array_pointer() noexcept ;

    array_pointer &     operator =( array_pointer && ) noexcept ;
    T *                 raw_pointer() const noexcept ;
    void                reset( T * ) noexcept ;

private:
    T *                 m_ptr ;
    void                do_delete() noexcept ;
} ;

}

#include "brz/array_pointer.tpp"
#endif
