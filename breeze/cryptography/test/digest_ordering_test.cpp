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

#include "breeze/cryptography/digest.hpp"
#include "breeze/cryptography/sha1_hasher.hpp"
#include "breeze/testing/testing.hpp"

#include <map>
#include <string>

int                 test_digest_ordering() ;

namespace {

void
check_usability_with_map()
{
    std::string const   s = "test" ;
    breeze::sha1_hasher const
                        hasher( s.cbegin(), s.cend() ) ;
    breeze::sha1_digest const
                        digest( hasher ) ;
    std::map< breeze::sha1_digest, int, breeze::sha1_digest::less >
                        m ;
    m[ digest ] = 1 ;
}

}

int
test_digest_ordering()
{
    return breeze::test_runner::instance().run(
        "Digest ordering",
        { check_usability_with_map } ) ;
}
