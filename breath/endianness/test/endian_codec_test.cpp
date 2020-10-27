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

#include "breath/endianness/endian_codec.hpp"
#include "breath/testing/testing.hpp"

#include <cstddef>
#include <cstdint>
#include <iterator>
#include <sstream>

int                 test_endian_codec() ;

namespace {

void check()
{
    using               breath::big_endian_policy ;
    using               breath::little_endian_policy ;

    std::uint32_t const value = 0x01020304;
    std::uint8_t        array[ 4 ] ;
    breath::endian_store< little_endian_policy >( value, &array[ 0 ] ) ;
    BREATH_CHECK( array[ 0 ] == 4 ) ;
    BREATH_CHECK( array[ 1 ] == 3 ) ;
    BREATH_CHECK( array[ 2 ] == 2 ) ;
    BREATH_CHECK( array[ 3 ] == 1 ) ;
    std::uint32_t const u = breath::endian_load< little_endian_policy,
                                                 std::uint32_t >(
                                                            &array[ 0 ]
                                                            ) ;
    BREATH_CHECK( u == value ) ;

    breath::endian_store< big_endian_policy >( value, &array[ 0 ] ) ;
    BREATH_CHECK( array[ 0 ] == 1 ) ;
    BREATH_CHECK( array[ 1 ] == 2 ) ;
    BREATH_CHECK( array[ 2 ] == 3 ) ;
    BREATH_CHECK( array[ 3 ] == 4 ) ;

    std::uint32_t const u2 = breath::endian_load< big_endian_policy,
                                                  std::uint32_t >(
                                                            &array[ 0 ]
                                                        ) ;
    BREATH_CHECK( u2 == value ) ;
}

void
check2()
{
    typedef breath::endian_codec< breath::big_endian_policy,
                                  std::size_t,
                                  unsigned int
                      > codec_type ;
    std::size_t const   amount = 24 ;
    unsigned int        repr[ 16 ] = {} ;
    codec_type::encode( amount, std::begin( repr ) ) ;

    //      std::size_t changes size in 64-bit mode, so take into
    //      account that the representation may "enlarge".
    // -----------------------------------------------------------------------
    BREATH_CHECK( repr[ sizeof amount / sizeof repr[ 0 ] - 1 ] == 24 ) ;
}

template< typename T, typename Byte >
void
check_type_that_fits_in_byte()
{
    Byte dest = 0 ;
    breath::endian_codec< breath::little_endian_policy,
                          T,
                          Byte >::encode( 10, &dest ) ;
    BREATH_CHECK( dest == 10 ) ;

    breath::endian_codec< breath::big_endian_policy,
                          T,
                          Byte >::encode( 20, &dest ) ;
    BREATH_CHECK( dest == 20 ) ;
}

void
check_input_output_iterators()
{
    std::uint64_t const value = 0x01'02'03'04'05'06'07'08;
    std::stringstream   ss ;

    breath::endian_codec<
        breath::big_endian_policy,
        std::uint64_t,
        std::uint8_t >::encode( value, std::ostream_iterator< int >( ss, " " ) ) ;

    BREATH_CHECK( ss.str() == "1 2 3 4 5 6 7 8 " ) ;

    std::uint64_t       read =
        breath::endian_codec<
            breath::big_endian_policy,
            std::uint64_t,
            std::uint8_t >::decode( std::istream_iterator< int >( ss ) ) ;

    BREATH_CHECK( read == value ) ;
}

}

int
test_endian_codec()
{
    using namespace breath ;

    return test_runner::instance().run( "endian_codec",
            { check,
              check2,
              check_type_that_fits_in_byte< unsigned char, unsigned int >,
              check_type_that_fits_in_byte< unsigned int,  unsigned long >,
              check_input_output_iterators } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
