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

#include <cstdint>
#include <iomanip>
#include <ios>
#include <iostream>
#include <ostream>
#include <string>

namespace {

//      Implementation notes:
//      ---------------------
//
//      See crc32.tpp for a (pseudo-)reference on the calculations.
// ---------------------------------------------------------------------------

std::uint32_t       byte_checksum( std::uint8_t byte )
{
    std::uint32_t const reversed_polynomial = 0xEDB88320 ;
    int const           char_bit = 8  ;
    std::uint32_t       checksum = byte ;

    for ( int i = 0 ; i < char_bit ; ++ i ) {
        checksum = checksum % 2 == 0
                        ? ( checksum >> 1 )
                        : ( checksum >> 1 ) ^ reversed_polynomial
                        ;
    }
    return checksum ;
}

}


int
main()
{
    int const           size = 256 ;
    int const           numbers_per_line = 6 ;
    int const           indent_size = 4 ;

    //      One space less than indent_size: this way we output every
    //      value with a leading space, simplifying the logic. (An extra
    //      comma will follow the last element, which is allowed.)
    // -----------------------------------------------------------------------
    std::string const   indent( indent_size - 1, ' ' ) ;

    std::ostream &      os = std::cout ;

    os.setf( std::ios_base::hex, std::ios_base::basefield ) ;
    os.fill( '0' ) ;
    os << "static std::uint_fast32_t const\n" << indent <<
          "                table[] =\n{\n" ;

    int                 column = 0 ;
    for ( int i = 0 ; i < size ; ++ i ) {
        if ( column == 0 ) {
            os << indent ;
        }
        std::uint32_t const value = byte_checksum(
            static_cast< std::uint8_t >( i ) ) ;
        os << " 0x" << std::setw( 8 ) << value << ',' ;
        ++ column ;
        if ( column == numbers_per_line ) {
            os << std::endl ;
            column = 0 ;
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
