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

#ifndef BREEZE_GUARD_fuCxVYYJ2LdcmZesVYlZ9PyrSKmKj97I
#define BREEZE_GUARD_fuCxVYYJ2LdcmZesVYlZ9PyrSKmKj97I

#include "breeze/top_level_namespace.hpp"

namespace breeze_ns {

//      subrange_adaptor:
//      =================
//
//!     \copybrief subrange_adaptor.hpp
//!
//!     Adapts a random or pseudo-random number generator to emit
//!     numbers in a subrange of its original range (see the
//!     max_for_subrange() facility).
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

    subrange_adaptor &  operator =( subrange_adaptor const & ) = delete ;

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

#include "brz/subrange_adaptor.tpp"
#endif
