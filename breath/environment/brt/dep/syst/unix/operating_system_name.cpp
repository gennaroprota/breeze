// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2007-2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/diagnostics/last_api_error.hpp"

#include <ostream>
#include <cstring>
#include <sys/utsname.h>

namespace breath {

std::ostream &
operator <<( std::ostream & dest, operating_system_name const & )
{
    utsname             un ;
    int const           ret = uname( &un ) ;

    if ( ret == -1 ) {
        throw last_api_error( "uname() failed" ) ;
    }

    return dest << un.sysname
                << ' ' << un.release
                << ' ' << un.version
                << ' ' << un.machine ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
