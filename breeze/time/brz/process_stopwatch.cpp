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

#include "breeze/time/process_stopwatch.hpp"
#include "breeze/text/to_string.hpp"
#include "breeze/porting/dependent_source.hpp"
#include BREEZE_DEPENDENT_SOURCE( system_family, process_stopwatch.cpp )

#include <ostream>
#include <sstream>

namespace breeze_ns {

double
process_duration::percentage_to_total() const
{
    return ( user + system ) / wall * 100 ;
}

std::string
process_duration::to_string() const
{
    static char const   indent[] = "    " ;
    std::ostringstream  oss ;
    oss << indent << "user time:       " << breeze::to_string( user )   << '\n'
        << indent << "system time:     " << breeze::to_string( system ) << '\n'
        << indent << "wall-clock time: " << breeze::to_string( wall )   << '\n'
        << indent ;

    oss.setf( std::ios::fixed, std::ios::floatfield ) ;
    oss.precision( 2 ) ;
    oss << "(" << percentage_to_total() << "% on behalf of this process)";

    if ( oss.fail() ) {
        throw std::runtime_error( "error in process_duration::to_string()" ) ;
    }

    return oss.str() ;
}

std::ostream &
operator <<( std::ostream & dest, process_duration const & d )
{
    return dest << d.to_string() ;
}

process_stopwatch::process_stopwatch( process_stopwatch::start_mode mode )
{
    if ( mode == auto_start ) {
        start() ;
    }
}

void
process_stopwatch::start()
{
    m_start = get_process_times() ;
}

process_duration
process_stopwatch::elapsed() const
{
    process_duration    result = get_process_times() ;
    result.user   -= m_start.user ;
    result.system -= m_start.system ;
    result.wall   -= m_start.wall ;

    return result ;
}

}
