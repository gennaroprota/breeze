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

#include "breeze/diagnostics/last_api_error.hpp"

#include <ostream>
#include <sys/utsname.h>

namespace breeze_ns {

std::string
operating_system_name::to_string() const
{
    utsname             un ;
    int const           ret = uname( &un ) ;

    if ( ret == -1 ) {
        throw last_api_error( "uname() failed" ) ;
    }

    return std::string( un.sysname ) +
                   ' ' + un.release  +
                  ", " + un.version  +
                  ", " + un.machine ;
}

std::ostream &
operator <<( std::ostream & dest, operating_system_name const & name )
{
    return dest << name.to_string() ;

}

}
