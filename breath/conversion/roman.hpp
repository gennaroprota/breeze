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
//!     A number that outputs in roman numerals.
// ---------------------------------------------------------------------------
class roman
{
public:
    //!     Constructs a roman number object corresponding to number
    //!     \c n.
    // -----------------------------------------------------------------------
    explicit            roman( int n ) ;

private:
    //      The implementation here is different from usual: rather than
    //      doing the conversion to roman numerals in the stream
    //      inserter, we do it in the constructor and store the
    //      resulting representation in a std::string object. Consider
    //      this implementation detail somewhat experimental.
    // -----------------------------------------------------------------------
    std::string         m_representation ;

    //!     Stream output operator: outputs the number in roman
    //!     numerals. The case of the letters is unspecified (this
    //!     allows us to support e.g. \c std::uppercase and
    //!     \c std::nouppercase in the future). But it's guaranteed that
    //!     all letters will have the same case.
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
