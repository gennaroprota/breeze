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

namespace breath {

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
    auto                curr = begin ;
    int                 count = 0 ;
    int                 column = 0 ;

    auto                do_output = [ & ]( char c )
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

    //  This code is ugly because we stick to input iterators and don't
    //  assume random access. Furthermore we have to check for the end
    //  of the range at each increment.
    //  ------------------------------------------------------------------
    while ( curr != end ) {
        do_output( alphabet[ static_cast< unsigned char>( *curr ) >> 2 ] ) ;
        ++ count ;
        auto                tmp = ( static_cast< unsigned char >( *curr )
                                                             & 0x03 ) << 4 ;

        if ( ++curr != end ) {
            ++ count ;
            tmp |= ( static_cast< unsigned char >( *curr ) & 0xf0 ) >> 4 ;
            do_output( alphabet[ tmp ] ) ;

            auto            tmp2 = ( static_cast< unsigned char >( *curr )
                                                                & 0x0f ) << 2 ;
            if ( ++curr != end ) {
                ++ count ;
                tmp2 |= static_cast< unsigned char >( *curr ) >> 6 ;
                do_output( alphabet[ tmp2 ] ) ;
                do_output( alphabet[ static_cast< unsigned char >(
                                                            *curr ) & 0x3f ] ) ;
                ++ curr ;
            } else {
                do_output( alphabet[ tmp2 ] ) ;
            }
        } else {
            do_output( alphabet[ tmp ] ) ;
        }
        count %= group_size ;
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
