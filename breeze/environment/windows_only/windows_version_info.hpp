// ===========================================================================
//                     Copyright 2007-2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Microsoft Windows version information.
// ---------------------------------------------------------------------------

#ifndef BREEZE_GUARD_XHTe6eJtKcY8TQSy4joG13QO3Eu5NfRF
#define BREEZE_GUARD_XHTe6eJtKcY8TQSy4joG13QO3Eu5NfRF

#include "breeze/top_level_namespace.hpp"
#include <string>

namespace breeze_ns {

//      windows_version_info:
//      =====================
//
//!     Microsoft Windows version information.
// ---------------------------------------------------------------------------
class windows_version_info
{
public:
    //!     Constructs a \c windows_version_info object.
    // -----------------------------------------------------------------------
                        windows_version_info() ;

    //!     Destroys a \c windows_version_info object.
    // -----------------------------------------------------------------------
                        ~windows_version_info() noexcept ;

    //!     Deleted copy constructor.
    // -----------------------------------------------------------------------
                        windows_version_info( windows_version_info const & )
                                                                   = delete ;

    //!     Deleted copy assignment operator.
    // -----------------------------------------------------------------------
    windows_version_info &
                        operator =( windows_version_info const & ) = delete ;

    //!     \return
    //!         The major version number of the operating system.
    // -----------------------------------------------------------------------
    int                 major_version() const ;

    //!     \return
    //!         The minor version number of the operating system.
    // -----------------------------------------------------------------------
    int                 minor_version() const ;

    //!     \return
    //!         The build number of the operating system.
    // -----------------------------------------------------------------------
    int                 build_number() const ;

    //!     \return
    //!         A (possibly empty) string with the edition of the
    //!         operating system. The return type could be <code>maybe<
    //!         std::string ></code> but I didn't want to introduce
    //!         another dependency.
    // -----------------------------------------------------------------------
    std::string         edition() const ;

    //!     \return
    //!         Whether the OS is 64-bit.
    // -----------------------------------------------------------------------
    static bool         is_64_bit() ;

    //!     \return
    //!         Whether the OS is a Windows client version.
    // -----------------------------------------------------------------------
    static bool         is_client() ;

    //!     \return
    //!         The major version number of the installed service pack,
    //!         if any. Zero if no service pack is installed. Note that
    //!         this ignores the minor number (which Microsoft doesn't
    //!         seem to be using, anyway).
    //!
    //!     \par Exceptions
    //!         A \c std::runtime_error (which can be a \c
    //!         last_api_error) if an error occurs.
    // -----------------------------------------------------------------------
    static int          service_pack_level() ;

private:
    static bool         is_wow64_process() ;

    int                 m_major_version ;
    int                 m_minor_version ;
    int                 m_build_number ;
} ;

}

#endif
