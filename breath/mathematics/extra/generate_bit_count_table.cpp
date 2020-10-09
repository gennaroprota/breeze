// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include <cstddef>
#include <iostream>
#include <string>

namespace {

int bit_count( unsigned value )
{
    int                 count = 0 ;
    while ( value != 0 ) {
        ++ count ;
        value &= ( value - 1 ) ;
    }

    return count ;
}

}

int
main()
{
    int const           size = 256 ;

    int const           numbers_per_line = 16 ;
    int const           indent_size = 4 ;

    //      One space less than indent_size: this way we output every
    //      value with a leading space, simplifying the logic. (An extra
    //      comma will follow the last element, which is allowed.)
    // -----------------------------------------------------------------------
    std::string const   indent( indent_size - 1, ' ' ) ;

    std::ostream &      os = std::cout ;

    os << "constexpr unsigned char"              << std::endl
       << "                    count_table[] = " << std::endl
       << "{"                                    << std::endl ;

    int                 column = 0;
    for ( int i = 0 ; i < size ; ++ i ) {
        if ( column == 0 ) {
            os << indent ;
        }
        os << ' ' << bit_count( static_cast< unsigned >( i ) ) << ',' ;
        ++ column ;
        if ( column == numbers_per_line ) {
            os << std::endl ;
            column = 0 ;
        }
    }
    os << "} ;" << std::endl ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
