// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include <array>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <ostream>

int
main()
{
    static char const   alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                     "abcdefghijklmnopqrstuvwxyz"
                                     "0123456789+/" ;

    int const           size = 256 ;
    int const           entries_per_row = 16 ;
    int const           invalid = -1 ;
    int const           indent_size = 4 ;

    //      One space less than indent_size: this way we output every
    //      value with a leading space, simplifying the logic. (An extra
    //      comma will follow the last element, which is allowed.)
    // -----------------------------------------------------------------------
    std::string const   indent( indent_size - 1, ' ' ) ;

    std::array< int, size >
                        table ;
    table.fill( invalid ) ;
    auto const          length = static_cast< int >( std::strlen( alphabet ) ) ;
    for ( int i = 0 ; i < length ; ++ i ) {
        table[ alphabet[ i ] ] = i ;
    }

    std::ostream &      os = std::cout ;

    os << "static int const    table[] =\n{\n" ;

    int                 column = 0 ;
    for ( int i = 0 ; i < size ; ++ i ) {
        if ( column == 0 ) {
            os << indent ;
        }
        os << ' ' << std::setw( 2 ) << table[ i ] << ',' ;
        ++ column ;
        if ( column == entries_per_row ) {
            os << std::endl ;
            column = 0 ;
        }
    }
    os << "} ;" << std::endl ;
}
