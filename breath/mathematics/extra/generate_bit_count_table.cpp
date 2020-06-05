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

#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <string>

int
main()
{
    int const           size = 256 ;
    std::array< int, size >
                        table ;

    class               bit_count
    {
    public:
        int                 operator()() noexcept
        {
            unsigned int        value = m_n ;
            int                 count = 0 ;
            while ( value != 0 ) {
                ++ count ;
                value &= ( value - 1 ) ;
            }
            ++ m_n ;
            return count ;
        }
    private:
        unsigned int        m_n = 0 ;
    } ;

    std::generate( table.begin(), table.end(), bit_count() ) ;
    int const           numbers_per_line = 16 ;
    int const           indent_size = 4 ;
    std::string const   indent( indent_size, ' ' ) ;

    std::ostream &      os = std::cout ;

    os << "constexpr unsigned char"              << std::endl
       << "                    count_table[] = " << std::endl
       << "{"                                    << std::endl ;
    os << indent ;
    for ( int i = 0 ; i < size ; ++ i ) {
        os << table[ i ] ;
        if ( i != ( size - 1 ) ) {
            os << ',' ;
        }
        if ( ( i + 1 ) % numbers_per_line == 0 &&
             i != ( size - 1 ) ) {
            os << std::endl << indent ;
        } else if ( i != ( size - 1 ) ) {
            os << ' ' ;
        } else {
            os << std::endl ;
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
