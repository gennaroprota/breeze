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

#include "breeze/endianness/endian_codec.hpp"
#include "breeze/testing/testing.hpp"

#include <cstddef>
#include <cstdint>
#include <iterator>
#include <sstream>

int                 test_endian_codec() ;

namespace {

void check()
{
    using               breeze::big_endian_policy ;
    using               breeze::little_endian_policy ;

    std::uint32_t const value = 0x01020304 ;
    std::uint8_t        array[ 4 ] ;
    breeze::endian_store< little_endian_policy >( value, &array[ 0 ] ) ;
    BREEZE_CHECK( array[ 0 ] == 4 ) ;
    BREEZE_CHECK( array[ 1 ] == 3 ) ;
    BREEZE_CHECK( array[ 2 ] == 2 ) ;
    BREEZE_CHECK( array[ 3 ] == 1 ) ;
    std::uint32_t const u = breeze::endian_load< little_endian_policy,
                                                 std::uint32_t >(
                                                            &array[ 0 ]
                                                            ) ;
    BREEZE_CHECK( u == value ) ;

    breeze::endian_store< big_endian_policy >( value, &array[ 0 ] ) ;
    BREEZE_CHECK( array[ 0 ] == 1 ) ;
    BREEZE_CHECK( array[ 1 ] == 2 ) ;
    BREEZE_CHECK( array[ 2 ] == 3 ) ;
    BREEZE_CHECK( array[ 3 ] == 4 ) ;

    std::uint32_t const u2 = breeze::endian_load< big_endian_policy,
                                                  std::uint32_t >(
                                                            &array[ 0 ]
                                                        ) ;
    BREEZE_CHECK( u2 == value ) ;
}

void
check2()
{
    typedef breeze::endian_codec< breeze::big_endian_policy,
                                  std::size_t,
                                  unsigned int
                      > codec_type ;
    std::size_t const   amount = 24 ;
    unsigned int        repr[ 16 ] = {} ;
    codec_type::encode( amount, std::begin( repr ) ) ;

    //      std::size_t changes size in 64-bit mode, so take into
    //      account that the representation may "enlarge".
    // -----------------------------------------------------------------------
    BREEZE_CHECK( repr[ sizeof amount / sizeof repr[ 0 ] - 1 ] == 24 ) ;
}

template< typename T, typename Byte >
void
check_type_that_fits_in_byte()
{
    Byte dest = 0 ;
    breeze::endian_codec< breeze::little_endian_policy,
                          T,
                          Byte >::encode( 10, &dest ) ;
    BREEZE_CHECK( dest == 10 ) ;

    breeze::endian_codec< breeze::big_endian_policy,
                          T,
                          Byte >::encode( 20, &dest ) ;
    BREEZE_CHECK( dest == 20 ) ;
}

void
check_input_output_iterators()
{
    std::uint64_t const value = 0x01'02'03'04'05'06'07'08 ;
    std::stringstream   ss ;

    breeze::endian_codec<
        breeze::big_endian_policy,
        std::uint64_t,
        std::uint8_t >::encode( value, std::ostream_iterator< int >( ss, " " ) ) ;

    BREEZE_CHECK( ss.str() == "1 2 3 4 5 6 7 8 " ) ;

    std::uint64_t       read =
        breeze::endian_codec<
            breeze::big_endian_policy,
            std::uint64_t,
            std::uint8_t >::decode( std::istream_iterator< int >( ss ) ) ;

    BREEZE_CHECK( read == value ) ;
}

}

int
test_endian_codec()
{
    return breeze::test_runner::instance().run(
        "endian_codec",
        { check,
          check2,
          check_type_that_fits_in_byte< unsigned char, unsigned int >,
          check_type_that_fits_in_byte< unsigned int,  unsigned long >,
          check_input_output_iterators } ) ;
}
