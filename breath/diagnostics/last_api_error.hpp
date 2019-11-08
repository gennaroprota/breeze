// ===========================================================================
//                        Copyright 2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief The last error from the OS API.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_HC9mIXMvniKHLa6eFGhdRhDkxlSaZErK
#define BREATH_GUARD_HC9mIXMvniKHLa6eFGhdRhDkxlSaZErK

#include "breath/diagnostics/exception.hpp"
#include <iosfwd>

namespace breath {

//      last_api_error:
//      ===============
//
//!     An exception class representing the last error encountered
//!     in an OS API call. It corresponds to \c GetLastError() under
//!     Windows and \c errno under Unix.
//!
//!     The idea is that after an unsuccessful API call you write:
//!
//!     <code>
//!         throw last_api_error( "<APIName>() failed" ) ;
//!     </code>
//!
//!     and you're done with error handling.
//!
//!     The class is OutputStreamable, so you can also use
//!     \c breath::to_string(), which gives more information than the
//!     member \c what(), but may throw.
//!
//!     \warning
//!         This class is experimental.
//!
//!     \warning
//!         Only throw an exception of type \c last_api_error if the
//!         return value of the last function you called in the current
//!         thread indicates that \c GetLastError() (if under Windows)
//!         or \c errno (if under Unix) is meaningful.
// ---------------------------------------------------------------------------
class last_api_error
    :   public exception
{
public:
    explicit            last_api_error( char const * ) noexcept ;
                        last_api_error( last_api_error const & ) noexcept ;
    virtual             ~last_api_error() noexcept override ;

    //!     \return
    //!         The code of the last error. A long long, which is enough
    //!         to accomodate both \c errno and the result of \c
    //!         GetLastError() under Windows.
    // -----------------------------------------------------------------------
    long long           code() const noexcept ;
    virtual char const *
                        what() const noexcept override ;

    void                operator =( last_api_error const & ) = delete ;

private:
    friend std::ostream &
                        operator <<( std::ostream &, last_api_error const & ) ;

    long long           m_last_error ;
    char                m_message[ 10 * 1024 - 1 ] ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
