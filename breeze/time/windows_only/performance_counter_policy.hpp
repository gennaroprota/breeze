// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A timer policy using Windows' \c
//!            QueryPerformanceCounter().
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_xQJo3uSTt7ypxnH7y1CyRR3fJM5i3dsb
#define BREEZE_GUARD_xQJo3uSTt7ypxnH7y1CyRR3fJM5i3dsb

#include "breeze/top_level_namespace.hpp"
#include <chrono>

namespace breeze_ns {

//      performance_counter_policy:
//      ===========================
//
//!     A timer policy using Windows' \c QueryPerformanceCounter().
// ---------------------------------------------------------------------------
class performance_counter_policy
{
public:
    //!     Deleted copy constructor.
    // -----------------------------------------------------------------------
    performance_counter_policy( performance_counter_policy const & ) = delete ;

    //!     Deleted copy assignment operator.
    // -----------------------------------------------------------------------
    performance_counter_policy &
                    operator =( performance_counter_policy const & ) = delete ;

    typedef std::chrono::duration< double, std::micro >
                        duration_type ;
                        performance_counter_policy() ;

    void                start() ;
    duration_type       elapsed() const ;
    duration_type       resolution() const ;

private:
    long long           m_start ;
    long long           m_frequency ;
} ;

}

#endif
