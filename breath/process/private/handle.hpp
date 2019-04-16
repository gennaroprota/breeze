// ===========================================================================
//                        Copyright 2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#ifndef BREATH_GUARD_0IbzhpmeQvdgWhXSSEDKYfNu88kSfPsS
#define BREATH_GUARD_0IbzhpmeQvdgWhXSSEDKYfNu88kSfPsS

#include "breath/idiom/declare_non_copyable.hpp"
#include <Windows.h>

namespace breath {
namespace process_private {

//      RAII class to automatically close a process handle.
// ---------------------------------------------------------------------------
class handle
{
public:
    BREATH_DECLARE_NON_COPYABLE( handle )

    explicit            handle( HANDLE h ) noexcept
                            :   m_handle( h )
                        {}
                        ~handle() noexcept
                        {
                            if ( m_handle != NULL ) {
                                // NOTE: the return value is ignored.
                                CloseHandle( m_handle ) ;
                            }
                        }
    HANDLE              get() const noexcept
                        {
                            return m_handle ;
                        }
private:
    HANDLE              m_handle ;
} ;

}
}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
