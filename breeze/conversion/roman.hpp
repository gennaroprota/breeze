// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A Roman numeral.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_hMt6bmZCT9RIwijJe5QSttMMotHJsr1N
#define BREEZE_GUARD_hMt6bmZCT9RIwijJe5QSttMMotHJsr1N

#include "breeze/top_level_namespace.hpp"
#include <iosfwd>
#include <string>

namespace breeze_ns {

//      roman:
//      ======
//
//!     \copybrief roman.hpp
// ---------------------------------------------------------------------------
class roman
{
public:
    //!     Constructs a Roman numeral corresponding to the number `n`.
    //!
    //!     \pre
    //!         1 <= n && n <= 3999
    // -----------------------------------------------------------------------
    explicit            roman( int n ) ;

    //!     \return
    //!         A string containing the Roman numeral. This will always
    //!         be all-uppercase. To get all-lowercase, use the stream
    //!         inserter, instead.
    //! ----------------------------------------------------------------------
    std::string         to_string() const ;

private:
    int                 m_value ;
} ;

//!\brief
//!     Outputs a Roman numeral to a stream.
//!
//!     The uppercase flag (`std::ios_base::uppercase`) is supported, so
//!     the user can obtain all-uppercase or all-lowercase.
//!
//!     \relatedalso roman.
// ---------------------------------------------------------------------------
std::ostream &      operator <<( std::ostream &, roman const & ) ;

}

#endif
