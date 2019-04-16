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
// -------------------------------------------------------------------------

#include "breath/idiom/declare_non_copyable.hpp"
#include <string>

namespace breath {

//      windows_version_info:
//      =====================
//
//!     Microsoft Windows version information.
// -------------------------------------------------------------------------
class windows_version_info
{
public:
    //! Constructs a \c windows_version_info object.
    // -----------------------------------------------------------------------
                        windows_version_info() ;

    //! Destroys a \c windows_version_info object.
    // -----------------------------------------------------------------------
                        ~windows_version_info() noexcept ;

    //! Deleted copy members.
    // -----------------------------------------------------------------------
    BREATH_DECLARE_NON_COPYABLE( windows_version_info )

    //! \return
    //!     The major version number of the operating system.
    // -----------------------------------------------------------------------
    int                 major_version() const ;

    //! \return
    //!     The minor version number of the operating system.
    // -----------------------------------------------------------------------
    int                 minor_version() const ;

    //! \return
    //!     The build number of the operating system.
    // -----------------------------------------------------------------------
    int                 build_number() const ;

    //! \return
    //!     A (possibly empty) string with the edition of the operating
    //!     system. The return type could be <code>maybe< std::string >
    //!     </code> but I didn't want to introduce another dependency.
    // -----------------------------------------------------------------------
    std::string         edition() const ;

    //! \return
    //!     Whether the OS is 64-bit.
    // -----------------------------------------------------------------------
    static bool         is_64_bit() ;

    //! \return
    //!     Whether the OS is a Windows client version.
    // -----------------------------------------------------------------------
    static bool         is_client() ;

    //! \return
    //!     The service pack level. Zero if no service pack is
    //!     installed.
    // -----------------------------------------------------------------------
    static int          service_pack_level() ;

private:
    static bool         is_wow64_process() ;

    int                 m_major_version ;
    int                 m_minor_version ;
    int                 m_build_number ;
} ;

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
