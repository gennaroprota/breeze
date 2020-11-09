// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/diagnostics/assert.hpp"
#include <climits>
#include <type_traits>

namespace breath_ns {

template< typename InputIter, typename OutputIter >
void
binary_to_base64( InputIter begin, InputIter end,
                  OutputIter out, int wrap_column )
{
    static_assert( CHAR_BIT == 8 &&
       ( std::is_same< typename InputIter::value_type, char >::value
      || std::is_same< typename InputIter::value_type, unsigned char >::value ),
                   "" ) ;

    BREATH_ASSERT( wrap_column >= 0 ) ;

    static char const   alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                     "abcdefghijklmnopqrstuvwxyz"
                                     "0123456789+/" ;
    int const           group_size = 3 ;
    int const           bits_per_base64_char = 6 ;
    int const           char_bit = CHAR_BIT ;

    int                 column = 0 ;

    auto                do_output = [ &out, &column, &wrap_column ]( char c )
    {
        *out = c ;
        ++ out ;
        ++ column ;
        if ( column == wrap_column ) {
            *out = '\n' ;
            ++ out ;
            column = 0 ;
        }
    } ;

    unsigned            accum = 0 ;
    int                 accum_bit_count = 0 ;
    auto                curr = begin ;
    int                 count = 0 ;

    while ( curr != end ) {
        accum = accum << char_bit | static_cast< unsigned char >( *curr ) ;
        accum_bit_count += char_bit ;
        ++ count ;
        count %= group_size ;

        while ( accum_bit_count >= bits_per_base64_char ) {
            int const       next = accum_bit_count - bits_per_base64_char ;
            auto            c = static_cast< unsigned char >( accum >> next ) ;
            do_output( alphabet[ c ] ) ;
            accum &= ( ( 1 << next ) - 1 ) ;
            accum_bit_count = next ;
        }

        ++ curr ;
    }

    if ( accum_bit_count != 0 ) {
        accum <<= ( bits_per_base64_char - accum_bit_count ) ;
        do_output( alphabet[ accum ] ) ;
    }

    for ( int i = 0 ; i < ( group_size - count ) % group_size ; ++ i ) {
        do_output( '=' ) ;
    }
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
