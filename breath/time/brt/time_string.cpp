// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2008-2011 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/time/time_string.hpp"
#include "breath/time/private/thread_safe_reentrant_time_functions.hpp"
#include "breath/idiom/maybe.hpp"
#include <time.h>

namespace breath {

//      IMPLEMENTATION NOTE:
//      --------------------
//      Intentionally I used a fixed size buffer here: the size is
//      plentiful for any date formatting need I could imagine, and
//      anything which involved dynamic allocation looked definitely
//      like over-engineering.
// ---------------------------------------------------------------------------
maybe< std::string >
time_string( std::string const & format, time_string_zone::zone zone )
{
    using namespace time_private ;

    maybe< std::string >
                        result ;

    time_t const        time_stamp( time( nullptr ) ) ;
    if ( time_stamp != static_cast< time_t >( -1 ) ) { // gps
        tm                  broken_down ;
        tm const * const    p( zone == time_string_zone::utc
                ? thread_safe_reentrant_gmtime(    &time_stamp, &broken_down )
                : thread_safe_reentrant_localtime( &time_stamp, &broken_down ) )
                        ;
        if ( p != nullptr ) {
            int const           max_size = 256 ;
            char                buffer[ max_size ] = {} ;
            if ( strftime( buffer, max_size, format.c_str(), &broken_down )
                    != 0 ) {
                result = buffer ;
            }
        }
    }

    return result ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
