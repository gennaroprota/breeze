// ===========================================================================
//                        Copyright 2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Random or pseudo-random number generator adaptor.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_fuCxVYYJ2LdcmZesVYlZ9PyrSKmKj97I
#define BREATH_GUARD_fuCxVYYJ2LdcmZesVYlZ9PyrSKmKj97I

#include "breath/top_level_namespace.hpp"

namespace breath_ns {

//      subrange_adaptor:
//      =================
//
//!     Adapts a random or pseudorandom number generator to emit
//!     numbers in a subrange of its original range (see the
//!     subrange_max facility).
//!
//!     \note
//!         Does NOT support min != 0.
// ---------------------------------------------------------------------------
template< typename Engine >
class subrange_adaptor
{
public:
    //!     The same as the Engine's result type.
    // -----------------------------------------------------------------------
    typedef typename Engine::result_type
                        result_type ;

    void                operator =( subrange_adaptor const & ) = delete ;

    //!     Constructs a subrange adaptor from a given Engine and a new max
    //!     value.
    // -----------------------------------------------------------------------
                        subrange_adaptor( Engine & e, result_type new_max ) ;

    //!     \return
    //!         A new random value in the adaptor's subrange.
    // -----------------------------------------------------------------------
    result_type         next() ;

private:
    Engine &            m_engine ;
    result_type const   m_max    ;

} ;

}

#include "brt/subrange_adaptor.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
