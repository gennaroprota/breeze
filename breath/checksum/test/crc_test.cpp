// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2016-2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/checksum/crc.hpp"
#include "breath/iteration/begin_end.hpp"
#include "breath/testing/testing.hpp"
#include <iostream>
#include <string>
#include <vector>

int                 test_crc() ;

namespace {

//      crc12_umts:
//      ===========
//
//      Traits for CRC-12/UMTS (aka CRC-12/3GPP).
//
//      This is an academic CRC created in 2009.
//
//      I didn't feel like exposing its traits in crc.hpp, but it allows
//      testing our implementation for the unusual case reflect_in =
//      false and reflect_out = true (the opposite of invented_crc, used
//      below).
// ---------------------------------------------------------------------------
struct crc12_umts
{
    typedef std::uint16_t   value_type ;

    static int        const width       = 12    ;
    static value_type const poly        = 0x80F ;
    static value_type const init        = 0     ;
    static bool       const reflect_in  = false ;
    static bool       const reflect_out = true  ;
    static value_type const xor_out     = 0     ;

    static value_type const check       = 0xDAF ;
} ;

//      invented_crc:
//      =============
//
//      Since (AFAIK) there's no CRC in actual use which has reflect_in
//      = true and reflect_out = false, we make up these parameters, in
//      order to test the implementation.
//
//      The result has been verified with:
//
//        <http://zorc.breitbandkatze.de/crc.html>;
//
//      this should be taken with a grain of salt, but the fact that two
//      independent implementations get the same results is a good sign.
// -----------------------------------------------------------------------
struct invented_crc
{
    typedef unsigned        value_type ;

    static int        const width       = 13     ;
    static value_type const poly        = 0xABD  ;
    static value_type const init        = 0x16EF ;
    static bool       const reflect_in  = true   ;
    static bool       const reflect_out = false  ;
    static value_type const xor_out     = 0x123  ;

    static value_type const check       = 0x197C ;
} ;

//      TODO: in theory, this test should be doable at compile time,
//      with a static_assert in the code of crc< Traits >; but that
//      isn't particularly easy to do (or I'm missing something
//      obvious).
// ---------------------------------------------------------------------------
template< typename CrcTraits >
void check_value_from_traits()
{
    char const          input[] = "123456789" ;
    int  const          len     = sizeof input - 1 ;

    BREATH_CHECK( breath::crc< CrcTraits >( input, input + len ).value() ==
        CrcTraits::check ) ;

    //      Now check in two steps.
    // -----------------------------------------------------------------------
    int const           step1_len = len / 2 ;
    breath::crc< CrcTraits >
                        crc ;
    crc.accumulate( input, input + step1_len ) ;
    crc.accumulate( input + step1_len, input + len ) ;
    BREATH_CHECK( crc.value() == CrcTraits::check ) ;

    //      Also check with iterators that are not to bytes.
    // -----------------------------------------------------------------------
    std::vector< int > const
                        int_input( input, input + len );

    BREATH_CHECK(
        breath::crc< CrcTraits >( int_input.cbegin(), int_input.cend() ).value()
            == CrcTraits::check ) ;
}

void
check_known_crc32s()
{
    struct
    {
        std::string         text ;
        unsigned long       crc32 ;
    } const             known[] =
    {
        { "",                                            0          },

        //      Following test vectors verified with:
        //
        //        <https://www.lammertbies.nl/comm/info/crc-calculation.html>.
        //
        //      Like for invented_crc (see above), take this addito
        //      salis grano.
        // -------------------------------------------------------------------
        { "The quick brown fox jumps over the lazy dog", 0x414FA339 },
        { "breath",                                      0x3A3B4FE3 },
        { " ",                                           0xE96CCF45 },
        { "A",                                           0xD3D99E8B },
        { "ABC",                                         0xA3830348 },
        { "Nel mezzo del cammin di nostra vita",         0x5BFBCBF8 }
      } ;

    for ( auto it = breath::cbegin( known ) ; it != breath::cend( known ) ;
                                                                       ++ it ) {
        BREATH_CHECK( breath::crc< breath::crc32 >(
            it->text.cbegin(), it->text.cend() ).value() == it->crc32 ) ;
    }
}

}

int
test_crc()
{
    using namespace breath ;

    return test_runner::instance().run( "crc",
        { check_value_from_traits< breath::crc16 >,
          check_value_from_traits< breath::crc32 >,
          check_value_from_traits< breath::crc16_ibm3740 >,
          check_value_from_traits< crc12_umts >,
          check_value_from_traits< invented_crc >,
          check_known_crc32s } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
