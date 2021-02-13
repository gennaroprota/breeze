// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/mathematics/ceiling_of_quotient.hpp"
#include <ostream>

namespace breeze_ns {

template< typename Traits >
std::ostream &
operator <<( std::ostream & dest, crc< Traits > const & crc )
{
    typedef typename Traits::value_type
                        value_type ;

    int const           digit_count =
        ceiling_of_quotient( Traits::width, 4 ) ;

    char                buffer[ digit_count + 1 ] ;
    char const * const  start = &buffer[ 0 ] ;
    char *              p     = &buffer[ 0 ] + digit_count ;
    value_type          value = crc.value() ;

    *p = '\0' ;
    while ( p != start ) {
        -- p ;
        *p = "0123456789ABCDEF"[ value & 0x0f ] ;
        //!     The following statement could just be 'value >>= 4' but
        //!     that gives the usual compiler warnings, so...
        // -------------------------------------------------------------------
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
