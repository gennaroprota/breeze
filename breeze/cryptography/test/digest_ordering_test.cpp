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

#include "breeze/cryptography/sha1.hpp"
#include "breeze/testing/testing.hpp"

#include <map>
#include <string>

int                 test_digest_ordering() ;

namespace {

void
check_usability_with_map()
{
    std::string const   s1 = "string #1" ;
    std::string const   s2 = "string #2" ;
    std::map< breeze::sha1_digest, int, breeze::sha1_digest::less >
                        m ;
    m[ breeze::sha1_digest( s1.cbegin(), s1.cend() ) ] = 1 ;
    m[ breeze::sha1_digest( s2.cbegin(), s2.cend() ) ] = 2 ;

    BREEZE_CHECK( m.size() == 2 ) ;
}

}

int
test_digest_ordering()
{
    return breeze::test_runner::instance().run(
        "Digest ordering",
        { check_usability_with_map } ) ;
}
