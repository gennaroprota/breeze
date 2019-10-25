// ===========================================================================
//                     Copyright 2006-2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Macro to declare a class non-copyable.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_BssKAsCiqQzBgpiZdcF0pqcl37YyLxoi
#define BREATH_GUARD_BssKAsCiqQzBgpiZdcF0pqcl37YyLxoi

//!     Handy macro to declare a class as non-copyable. It is better
//!     invoked in a public section of the class definition (because
//!     this improves the error messages emitted if a copy is
//!     attempted).
// ---------------------------------------------------------------------------
#define BREATH_DECLARE_NON_COPYABLE( class_name )                       \
                                                                        \
                        class_name( class_name const & ) = delete ;     \
    void                operator =( class_name const & ) = delete ;     \
                                                                     /**/

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
