// ===========================================================================
//                        Copyright 2011 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Returns the textual representation of an object.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_JRFfcCLm3oqVulEWGOycMApryPN2pq33
#define BREEZE_GUARD_JRFfcCLm3oqVulEWGOycMApryPN2pq33

#include "breeze/top_level_namespace.hpp"
#include <chrono>
#include <locale>
#include <string>

namespace breeze_ns {

//      to_string():
//      ============
//
//!     \copybrief to_string.hpp
//!
//!     \return
//!         The textual representation of its argument. If `T` has a
//!         `to_string() const` member function taking no arguments,
//!         this template will use that. Otherwise, it will use
//!         `breeze::to_string( object, std::locale() )`, which requires
//!         a stream inserter.
// ---------------------------------------------------------------------------
template< typename T >
std::string         to_string( T const & object ) ;

//      to_string():
//      ============
//
//!\brief
//!     Returns the textual representation of a `std::chrono::duration`.
//!
//!     This is useful for pre-C++20 code (C++20 has a stream inserter
//!     for `std::chrono::duration`s.)
// ---------------------------------------------------------------------------
template< typename Rep, typename Period >
std::string         to_string( std::chrono::duration< Rep, Period > d ) ;

//      to_string():
//      ============
//
//!     \copybrief to_string.hpp
//!
//!     \return
//!         The textual representation of its argument. The
//!         representation depends, in general, on `loc`. This template
//!         requires a stream inserter.
//!
//!     \par Exceptions
//!         A `std::runtime_error` (or a `std::bad_alloc`) if the
//!         conversion fails.
// ---------------------------------------------------------------------------
template< typename OutputStreamable >
std::string         to_string( OutputStreamable const &,
                               std::locale const & loc ) ;

}

#include "brz/to_string.tpp"
#endif
