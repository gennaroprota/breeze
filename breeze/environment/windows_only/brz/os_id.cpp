// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2007-2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/environment/windows_only/os_id.hpp"
#include "breeze/environment/windows_only/windows_version_info.hpp"

#include <ostream>

namespace breeze_ns {
namespace           {

//      Attention: keep in sync with the enum definition in the .hpp
//      file.
// ---------------------------------------------------------------------------
char const * const  names[] =
{
    "Unknown Windows variant",

    "Windows 2000",
    "Windows XP",
    "Windows Server 2003",
    "Windows Home Server",
    "Windows Storage Server 2003",
    "Windows Server 2003 R2",
    "Windows XP Professional x64 Edition",
    "Windows Vista",
    "Windows Server 2008",
    "Windows Server 2008 R2",
    "Windows 7",
    "Windows 8",
    "Windows Server 2012",
    "Windows 8.1",
    "Windows Server 2012 R2",
    "Windows 10",
    "Windows Server 2016"
} ;

}

std::ostream &
operator <<( std::ostream & dest, os_id id )
{
    dest << breeze::names[ static_cast< int >( id ) ] ;

    windows_version_info const
                        info ;
    std::string const   edition = info.edition() ;
    if ( ! edition.empty() ) {
        dest << ' ' << edition ;
    }

    int const           sp = windows_version_info::service_pack_level() ;
    if ( sp != 0 ) {
        dest << " Service Pack " << sp ;
    }

    if ( windows_version_info::is_64_bit() ) {
        dest << ", 64-bit" ;
    }

    return dest << " (" << info.major_version() << '.' << info.minor_version()
                << ", build " << info.build_number() << ')' ;
}

}
