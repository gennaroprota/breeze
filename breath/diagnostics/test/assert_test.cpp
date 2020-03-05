// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/diagnostics/assert.hpp"

constexpr int
check_constexpr()
{
    BREATH_ASSERT( true ) ;
    return 1 ;
}

int
main()
{
    //      TODO: we'd need tests to verify that types other than bool
    //      or cv-qualified bool don't compile. And that
    //      BREATH_ASSERT( false ) aborts the program. I'll provide them
    //      when we'll have the necessary infrastructure for such tests.
    // -----------------------------------------------------------------------
    bool            b1 = true ;
    bool const      b2 = true ;
    bool volatile   b3 = true ;
    bool const volatile
                    b4 = true ;

    BREATH_ASSERT( b1 ) ;
    BREATH_ASSERT( b2 ) ;
    BREATH_ASSERT( b3 ) ;
    BREATH_ASSERT( b4 ) ;

    constexpr int       n = check_constexpr() ;
    static_cast< void >( n ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
