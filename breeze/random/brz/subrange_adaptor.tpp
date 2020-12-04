// ===========================================================================
//                     Copyright 2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/diagnostics/assert.hpp"
#include "breeze/preprocessing/prevent_macro_expansion.hpp"
#include "breeze/random/max_for_subrange.hpp"

namespace breeze_ns {

template< typename Engine >
subrange_adaptor< Engine >::subrange_adaptor( Engine & e, result_type new_max)
    :   m_engine( e ), m_max( new_max )
{
    //      Parenthesizing the expression m_engine.max, as Visual
    //      Studio 2017 has problems with BREEZE_PREVENT_MACRO_EXPANSION.
    // -----------------------------------------------------------------------
    BREEZE_ASSERT( m_max <= (m_engine.max)() ) ;
}

template< typename Engine >
typename subrange_adaptor< Engine >::result_type
subrange_adaptor< Engine >::next()
{
    if ( m_engine.max BREEZE_PREVENT_MACRO_EXPANSION () == m_max ) {
        return m_engine.next() ; // subrange coincides with full range
    }

    auto                n = m_engine.next() ;
    unsigned long const sub_max =
                    breeze::max_for_subrange( m_max,
                              m_engine.max BREEZE_PREVENT_MACRO_EXPANSION () ) ;
    while ( n > sub_max ) {
        n = m_engine.next() ;
    }
    return n % ( m_max + 1 ) ;
}

}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
