// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2021 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/time/process_timer.hpp"
#include "breeze/text/to_string.hpp"
#include "breeze/porting/dependent_source.hpp"
#include BREEZE_DEPENDENT_SOURCE( system_family, process_timer.cpp )

#include <ostream>
#include <sstream>

namespace breeze_ns {

std::string
process_duration::to_string() const
{
    static char const   indent[] = "    " ;
    std::ostringstream  oss ;
    oss << indent << "user time:   " << breeze::to_string( user )   << '\n'
        << indent << "system time: " << breeze::to_string( system ) ;

    if ( oss.fail() ) {
        throw std::runtime_error( "error in process_duration::to_string()" ) ;
    }

    return oss.str() ;
}

std::ostream &
operator <<( std::ostream & dest, process_duration const & t )
{
    return dest << t.to_string() ;
}

process_timer::process_timer( process_timer::start_mode mode )
{
    if ( mode == auto_start ) {
        start() ;
    }
}

void
process_timer::start()
{
    m_start = get_process_times() ;
}

process_duration
process_timer::elapsed() const
{
    process_duration    result = get_process_times() ;
    result.user   -= m_start.user ;
    result.system -= m_start.system ;

    return result ;
}

}
