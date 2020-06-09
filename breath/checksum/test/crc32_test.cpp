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

#include "breath/checksum/crc32.hpp"
#include "breath/iteration/begin_end.hpp"
#include "breath/testing/check.hpp"
#include "breath/testing/console_reporter.hpp"
#include "breath/testing/test_runner.hpp"
#include <iostream>
#include <ostream>
#include <string>

int                 test_crc32() ;

namespace {

void
check_known()
{
    struct
    {
        std::string text ;
        unsigned long crc32 ;
    } const             known[] =
    {
        { "",                                            0x0        },

        // Following test vectors verified with:
        //   <https://www.lammertbies.nl/comm/info/crc-calculation.html>
        //
        { "The quick brown fox jumps over the lazy dog", 0x414FA339 },
        { "123456789",                                   0xCBF43926 },
        { "breath",                                      0x3A3B4FE3 },
        { " ",                                           0xE96CCF45 },
        { "A",                                           0xD3D99E8B },
        { "ABC",                                         0xA3830348 },
        { "Nel mezzo del cammin di nostra vita",         0x5BFBCBF8 }
      } ;

    for ( auto it = breath::cbegin( known ) ; it != breath::cend( known ) ;
                                                                       ++ it ) {
        BREATH_CHECK( breath::crc32( it->text.cbegin(), it->text.cend() ) ==
                                                                   it->crc32 ) ;
    }
}

}

int
test_crc32()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { check_known } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
