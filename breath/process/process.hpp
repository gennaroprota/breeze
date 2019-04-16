// ===========================================================================
//                        Copyright 2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Represents a system process.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_ZrGNfF85u9RhKIbhXAPdD2JlFPjWlGjV
#define BREATH_GUARD_ZrGNfF85u9RhKIbhXAPdD2JlFPjWlGjV

#include "breath/process/private/process_id_type.hpp"
#include "breath/idiom/declare_non_copyable.hpp"
#include "breath/idiom/maybe.hpp"
#include <string>

namespace breath {

//      process:
//      ========
//
//!     A system process.
// ---------------------------------------------------------------------------
class process
{
public:
    BREATH_DECLARE_NON_COPYABLE( process )

    typedef process_id_type
                        id_type ;

                        process() ;
                        ~process() noexcept ;
    id_type             id() const ;

    void                start( std::string const & app_name,
                               std::string const & arguments,
                               maybe< unsigned long > const & timeout_in_ms =
                                            maybe< unsigned long >() ) ;
    void                kill() ;
    void                terminate() ;

private:
    class               impl ;
    impl * const        m_impl ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
