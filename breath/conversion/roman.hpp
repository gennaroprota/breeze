// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Roman numerals.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_hMt6bmZCT9RIwijJe5QSttMMotHJsr1N
#define BREATH_GUARD_hMt6bmZCT9RIwijJe5QSttMMotHJsr1N

#include <iosfwd>
#include <string>

namespace breath {

//      roman:
//      ======
//
//!     A number that outputs in Roman numerals.
// ---------------------------------------------------------------------------
class roman
{
public:
    //!     Constructs a Roman number object corresponding to number
    //!     \c n.
    //!
    //!     \pre
    //!         1 <= n && n <= 3999
    // -----------------------------------------------------------------------
    explicit            roman( int n ) ;

private:
    int                 m_value ;

    //!     Stream output operator: outputs the number in Roman
    //!     numerals. The uppercase flag (\c std::ios_base::uppercase)
    //!     is supported, so the user can obtain all-uppercase or
    //!     all-lowercase.
    // -----------------------------------------------------------------------
    friend std::ostream &
                    operator <<( std::ostream &, roman const & ) ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
