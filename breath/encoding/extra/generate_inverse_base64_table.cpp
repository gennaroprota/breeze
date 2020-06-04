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
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <iterator>
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
    std::array< int, size >
                        table ;
    table.fill( invalid ) ;
    for ( std::size_t i = 0 ; i < std::size( alphabet ) - 1 ; ++ i ) {
        table[ alphabet[ i ] ] = static_cast< int >( i ) ;
    }

    std::ostream &      os = std::cout ;

    os << "static int const    table[] = \n{\n    " ;
    for ( int i = 0 ; i < size ; ++ i ) {
        os << std::setw( 2 ) << table[ i ] ;
        if ( i != ( size - 1 ) ) {
            os << ", " ;
        }
        if ( ( i + 1 ) % entries_per_row == 0 ) {
            os << "\n    " ;
        }
    }
    os << "\n} ;" << std::endl ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
