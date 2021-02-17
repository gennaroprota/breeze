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
#include <locale>
#include <string>

namespace breeze_ns {

//      to_string():
//      ============
//
//!     \return
//!         The textual representation of its argument. If \c T has a
//!         <code>to_string() const</code> member function taking no
//!         arguments, this template will use that. Otherwise, it will
//!         use <code>breeze::to_string( object, std::locale() )</code>.
// ---------------------------------------------------------------------------
template< typename T >
std::string         to_string( T const & object ) ;

//      to_string():
//      ============
//
//!     \return
//!         The textual representation of its argument. The
//!         representation depends, in general, on \c loc.
//!
//!     \par Exceptions
//!         A \c std::runtime_error if the conversion fails.
// ---------------------------------------------------------------------------
template< typename OutputStreamable >
std::string         to_string( OutputStreamable const &,
                               std::locale const & loc ) ;

}

#include "brz/to_string.tpp"
#endif
