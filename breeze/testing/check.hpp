// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Macros for a single check within unit tests.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_EFlfreUFA16SG5tXxNJpWtUHWTCfIjaD
#define BREEZE_GUARD_EFlfreUFA16SG5tXxNJpWtUHWTCfIjaD

#include "breeze/diagnostics/assert.hpp"
#include "breeze/testing/test_exception.hpp"

#define BREEZE_CHECK( condition )                                             \
            do {                                                              \
                if ( ! ( condition ) ) {                                      \
                    throw breeze::test_exception( # condition,                \
                                                  __FILE__, __LINE__ ) ;      \
                }                                                             \
            } while ( false )                                              /**/


// For PVS-Studio:
// -V:BREEZE_CHECK_THROW:565
// ---------------------------------------------------------------------------
#define BREEZE_CHECK_THROW( exception_type, expression )                      \
            do {                                                              \
                bool threw_as_expected = false ;                              \
                bool threw_but_wrong_type = false ;                           \
                try {                                                         \
                    expression ;                                              \
                } catch ( exception_type const & ) {                          \
                    threw_as_expected = true ;                                \
                } catch ( ... ) {                                             \
                    threw_but_wrong_type = true ;                             \
                }                                                             \
                BREEZE_CHECK( ! threw_but_wrong_type ) ;                      \
                BREEZE_CHECK( threw_as_expected ) ;                           \
            } while ( false )                                              /**/

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
