// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/iteration/begin_end.hpp"
#include "breeze/mathematics/rounded_up_quotient.hpp"
#include <ostream>

namespace breeze_ns {

template< typename Traits >
std::ostream &
operator <<( std::ostream & dest, crc< Traits > const & crc )
{
    typedef typename Traits::value_type
                        value_type ;

    int const           digit_count =
        rounded_up_quotient( Traits::width, 4 ) ;

    char                buffer[ digit_count + 1 ] ;
    auto const          start = breeze::begin( buffer ) ;
    auto                iter  = breeze::end( buffer ) ;
    value_type          value = crc.value() ;

    -- iter ;
    *iter = '\0' ;
    while ( iter != start ) {
        -- iter ;
        *iter = "0123456789ABCDEF"[ value & 0x0f ] ;
        value = static_cast< value_type >( value >> 4 ) ;
    }

    dest << buffer ;
    return dest ;
}

}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
