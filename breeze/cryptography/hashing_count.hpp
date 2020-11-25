// ===========================================================================
//                     Copyright 2006-2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Hashing count policy.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_TFkXJUZ0hYDDlcmPKYMI9GfC5n42i9kF
#define BREEZE_GUARD_TFkXJUZ0hYDDlcmPKYMI9GfC5n42i9kF

#include "breeze/top_level_namespace.hpp"
#include <stdexcept>

namespace breeze_ns {

//!     \brief
//!         Count policy for the hashing algorithms.
// ---------------------------------------------------------------------------
class hashing_count
{
public:
    class exception ;

    //!     \brief
    //!         The type of exceptions emitted if the input sequence to
    //!         a hashing algorithm is too long.
    //
    //      Note: defined in-class as otherwise Doxygen doesn't pick its
    //      documentation up. (Problem encountered with Doxygen 1.8.18.)
    // -----------------------------------------------------------------------
    class exception
        :   public std::length_error
    {
    public:
        explicit            exception( char const * what_message ) ;
    } ;

    enum type
    {
        wraps,
        is_limited
    } ;

    static void         on_length_exhausted( type t ) ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
