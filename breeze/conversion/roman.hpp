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
//!\copybrief roman.hpp
// ---------------------------------------------------------------------------
class roman
{
public:
    //!     Constructs a Roman numeral corresponding to number \c n.
    //!
    //!     \pre
    //!         1 <= n && n <= 3999
    // -----------------------------------------------------------------------
    explicit            roman( int n ) ;

private:
    int                 m_value ;

    //!     Stream output operator: outputs the Roman numeral. The
    //!     uppercase flag (\c std::ios_base::uppercase) is supported,
    //!     so the user can obtain all-uppercase or all-lowercase.
    // -----------------------------------------------------------------------
    friend std::ostream &
                    operator <<( std::ostream &, roman const & ) ;
} ;

}

#endif
