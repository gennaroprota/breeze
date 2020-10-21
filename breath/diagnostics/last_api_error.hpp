// ===========================================================================
//                        Copyright 2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief The last error encountered by the calling thread in an OS
//!            API call.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_HC9mIXMvniKHLa6eFGhdRhDkxlSaZErK
#define BREATH_GUARD_HC9mIXMvniKHLa6eFGhdRhDkxlSaZErK

#include "breath/top_level_namespace.hpp"
#include <iosfwd>
#include <stdexcept>

namespace breath_ns {

//      last_api_error:
//      ===============
//
//!     \copybrief last_api_error.hpp
//!
//!     It corresponds to \c GetLastError() under Windows and \c errno
//!     under Unix.
//
//!     This class can be used in two ways:
//!
//!      - As an exception type;
//!
//!        the idea is that after an unsuccessful API call you write:
//!
//!        <code>
//!            throw last_api_error( "<APIName>() failed" ) ;
//!        </code>
//!
//!        and you're done with error handling.
//!
//!      - As a convenience facility to get both the error code and the
//!        error message for the last error.
//!
//!     The class is <tt>OutputStreamable</tt>, so you can also use \c
//!     breath::to_string(), which gives more information than the
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
    :   public std::runtime_error
{
public:
    explicit            last_api_error( char const * ) ;
                        last_api_error( last_api_error const & ) noexcept ;
    virtual             ~last_api_error() noexcept override ;

    //!     \return
    //!         The code of the last error. A <code>long long</code>,
    //!         which is enough to accomodate both \c errno and the
    //!         result of \c GetLastError() under Windows.
    // -----------------------------------------------------------------------
    long long           code() const noexcept ;

    last_api_error &    operator =( last_api_error const & ) = delete ;

private:

    typedef std::runtime_error
                        base_type ;

    friend std::ostream &
                        operator <<( std::ostream &, last_api_error const & ) ;

    long long           m_last_error ;

    //      See the comments in the implementation files for the purpose
    //      of this private constructor.
    // -----------------------------------------------------------------------
                        last_api_error( char const * p, long long error_code ) ;

} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
