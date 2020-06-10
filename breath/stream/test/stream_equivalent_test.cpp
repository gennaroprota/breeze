// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2019 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/stream/stream_equivalent.hpp"
#include "breath/testing/testing.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <istream>
#include <locale>
#include <ostream>
#include <sstream>

int                 test_stream_equivalent() ;

namespace {

void
check_good_streams()
{
    using breath::stream_equivalent ;
    std::stringstream   str ;

    str.tie( &std::cout ) ;
    str.imbue( std::locale::classic() ) ;
    str.exceptions( std::ios_base::badbit ) ;

    {
        stream_equivalent< std::stringstream >
                            equiv( str ) ;
        auto &              dest = equiv.get() ;

        dest.setf( std::ios_base::hex, std::ios_base::basefield ) ;
        dest.fill( '0' ) ;
        dest << std::setw( 2 ) << 15 ;
        BREATH_CHECK( str.str() == "0f" ) ;
    }

    BREATH_CHECK( str.rdstate() == std::ios_base::goodbit ) ;

    BREATH_CHECK( ( str.flags() & std::ios::hex ) == 0 ) ;
    BREATH_CHECK( str.fill() == ' ' ) ;
    BREATH_CHECK( str.width() == 0 ) ;

    BREATH_CHECK( str.tie() == &std::cout ) ;
    BREATH_CHECK( str.getloc() == std::locale::classic() ) ;
    BREATH_CHECK( str.exceptions() == std::ios_base::badbit ) ;
}

void
check_non_good_streams()
{
    using breath::stream_equivalent ;
    std::fstream        fs ;
    fs.clear( std::ios_base::failbit ) ;

    fs.tie( &std::cout ) ;
    fs.imbue( std::locale::classic() ) ;
    try {
        fs.exceptions( std::ios_base::failbit ) ;
    } catch ( std::ios_base::failure & ) { // -V565 (for PVS-Studio)
    }

    {
        stream_equivalent< std::fstream >
                            equiv( fs ) ;
        auto &              dest = equiv.get() ;

        fs.clear( std::ios_base::eofbit ) ;

        dest.setf( std::ios_base::hex, std::ios_base::basefield ) ;
        dest.fill( '*' ) ;
        int const           dummy_not_actually_output = 1 ;
        dest << std::setw( 256 ) << dummy_not_actually_output ;
        BREATH_CHECK( dest.width() == 256 ) ;
    }

    BREATH_CHECK( fs.rdstate() == ( std::ios_base::failbit |
                                    std::ios_base::eofbit    ) ) ;

    BREATH_CHECK( ( fs.flags() & std::ios_base::hex ) == 0 ) ;
    BREATH_CHECK( fs.fill() == ' ' ) ;
    BREATH_CHECK( fs.width() == 0 ) ;

    BREATH_CHECK( fs.tie() == &std::cout ) ;
    BREATH_CHECK( fs.getloc() == std::locale::classic() ) ;
    BREATH_CHECK( fs.exceptions() == std::ios_base::failbit ) ;
}

void
check_input_or_output_only_streams()
{
    using breath::stream_equivalent ;

    std::istream        is( std::cin.rdbuf() ) ;
    {
        stream_equivalent< std::istream >
                            equiv( is ) ;
        auto &              dest = equiv.get() ;
        static_cast< void >( dest ) ;
    }

    std::ostream        os( std::cout.rdbuf() ) ;
    {
        stream_equivalent< std::ostream >
                            equiv( os ) ;
        auto &              dest = equiv.get() ;
        static_cast< void >( dest ) ;
    }
}

}

int
test_stream_equivalent()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( "stream_equivalent",
                                        { check_good_streams,
                                          check_non_good_streams,
                                          check_input_or_output_only_streams }
                                      ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
