// ===========================================================================
//                     Copyright 2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/diagnostics/assert.hpp"
#include "breath/preprocessing/prevent_macro_expansion.hpp"
#include "breath/random/subrange_max.hpp"

namespace breath {

template< typename Engine >
subrange_adaptor< Engine >::subrange_adaptor( Engine & e, result_type new_max)
    :   m_engine( e ), m_max( new_max )
{
    //      Parenthesizing the expression m_engine.max, as Visual
    //      Studio 2017 has problems with BREATH_PREVENT_MACRO_EXPANSION.
    // ---------------------------------------------------------------------
    BREATH_ASSERT( m_max <= (m_engine.max)() ) ;
}

template< typename Engine >
typename subrange_adaptor< Engine >::result_type
subrange_adaptor< Engine >::next()
{
    if ( m_engine.max BREATH_PREVENT_MACRO_EXPANSION () == m_max ) {
        return m_engine.next() ; // subrange coincides with full range
    }

    auto                n ( m_engine.next() ) ;
    unsigned long const sub_max =
                    breath::subrange_max( m_max,
                              m_engine.max BREATH_PREVENT_MACRO_EXPANSION () ) ;
    while ( n > sub_max ) {
        n = m_engine.next() ;
    }
    return n % ( m_max + 1 ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
