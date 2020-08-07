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

#include <algorithm>
#include <array>
#include <cstdint>
#include <iomanip>
#include <ios>
#include <iostream>
#include <ostream>
#include <string>

namespace {

//      Note:
//          if you change this type, change it in the output below, too.
// -----------------------------------------------------------------------
typedef std::uint_fast32_t
                    fast32_type ;

//      Implementation:
//          see crc32.tpp for a (pseudo-)reference on the calculations.
// ---------------------------------------------------------------------------
class               byte_checksum
{
public:
    fast32_type         operator()() noexcept
    {
        fast32_type const   reversed_polynomial = 0xEDB88320uL ;
        int const           char_bit = 8 ;
        auto                checksum = m_n ;
        ++ m_n ;

        for ( int i = 0 ; i < char_bit ; ++ i ) {
            checksum = checksum % 2 == 0
                            ? ( checksum >> 1 )
                            : ( checksum >> 1 ) ^ reversed_polynomial
                            ;
        }
        return checksum ;
    }

private:
    fast32_type     m_n = 0 ;
} ;

}


int
main()
{
    int const           size = 256 ;
    std::array< fast32_type, size >
                        table ;

    std::generate( table.begin(), table.end(), byte_checksum() ) ;
    int const           numbers_per_line = 6 ;
    int const           indent_size = 4 ;
    std::string const   indent( indent_size, ' ' ) ;

    std::ostream &      os = std::cout ;

    os.setf( std::ios_base::hex, std::ios_base::basefield ) ;
    os.fill( '0' ) ;
    os << "static std::uint_fast32_t const\n" << indent <<
          "                    table[] =\n{\n" << indent ;
    for ( int i = 0 ; i < size ; ++ i ) {
        os << "0x" << std::setw( 8 ) << table[ i ] ;
        if ( i != ( size - 1 ) ) {
            os << ',' ;
        }
        if ( ( i + 1 ) % numbers_per_line == 0 ) {
            os << '\n' << indent ;
        } else if ( i != ( size - 1 ) ) {
            os << ' ' ;
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
