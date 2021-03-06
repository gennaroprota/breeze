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
//!     a pointer. An `array_pointer< T >` is similar to a `unique_ptr<
//!     T[], std::default_delete< T[] > >` but this template was written
//!     way before C++11.
//!
//!     Like for `unique_ptr`, instances of this template satisfy the
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

    //!     Constructs an `array_pointer` that doesn't own any array.
    //!
    //!     \post
    //!         raw_pointer() == nullptr
    // -----------------------------------------------------------------------
                        array_pointer() noexcept ;

    //!     Sets the internal pointer to `p`, taking ownership of the
    //!     pointed to array if `p` is non-null (in which case, the
    //!     array must have been allocated with `new []`.
    // -----------------------------------------------------------------------
    explicit            array_pointer( T * p ) noexcept ;

    //!     Move constructs from another `array_pointer`.
    // -----------------------------------------------------------------------
                        array_pointer( array_pointer && ) noexcept ;

    //!     Executes `delete [] raw_pointer()`.
    //!
    //!     Requires for `T` to be a complete type at the point of
    //!     instantiation.
    // ----------------------------------------------------------------------.
                        ~array_pointer() noexcept ;

    //!     Move assigns from another `array_pointer`.
    // -----------------------------------------------------------------------
    array_pointer &     operator =( array_pointer && ) noexcept ;

    //!     \return
    //!         A pointer to the owned array.
    // -----------------------------------------------------------------------
    T *                 raw_pointer() const noexcept ;

    //!     If the argument equals `raw_pointer()`, does nothing;
    //!     otherwise, executes `delete [] raw_pointer()` and sets the
    //!     internal pointer to the argument.
    //!
    //!     Requires for `T` to be a complete type at the point of
    //!     instantiation.
    //!
    //!     \post
    //!         raw_pointer() == p
    // -----------------------------------------------------------------------
    void                reset( T * p ) noexcept ;

private:
    T *                 m_ptr ;
    void                do_delete() noexcept ;
} ;

}

#include "brz/array_pointer.tpp"
#endif
