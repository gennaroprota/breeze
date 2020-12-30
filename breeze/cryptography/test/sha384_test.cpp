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

#include "breeze/cryptography/sha384_hasher.hpp"
#include "breeze/cryptography/digest.hpp"
#include "breeze/memory/amount_of_physical_memory.hpp"
#include "breeze/text/to_string.hpp"
#include "breeze/testing/testing.hpp"

#include <cstddef>
#include <iostream>
#include <string>

int                 test_sha384() ;

namespace {

//      These test vectors come from:
//
// [1]   <http://csrc.nist.gov/groups/ST/toolkit/documents/Examples/SHA384.pdf>
//      and
// [2]   <http://www.di-mgt.com.au/sha_testvectors.html>
//
//      The latter is not a primary source but I wanted more test
//      vectors.
// ---------------------------------------------------------------------------
void
check()
{
    {
        std::string const   s ; // [2]
        breeze::sha384_hasher const
                            hasher( s.cbegin(), s.cend() ) ;
        BREEZE_CHECK( breeze::to_string( breeze::sha384_digest( hasher ) )
            == "38b060a751ac96384cd9327eb1b1e36a21fdb71114be0743"
               "4c0cc7bf63f6e1da274edebfe76f65fbd51ad2f14898b95b" ) ;
    }
    {
        std::string const   s( "abc" ) ; // [1]
        breeze::sha384_hasher const
                            hasher( s.cbegin(), s.cend() ) ;
        BREEZE_CHECK( breeze::to_string( breeze::sha384_digest( hasher ) )
            == "cb00753f45a35e8bb5a03d699ac65007272c32ab0eded163"
               "1a8b605a43ff5bed8086072ba1e7cc2358baeca134c825a7" ) ;
    }
    {
        //      16,777,216 repetitions of 'piece' ( [2] )
        //
        //      This test will need a 1GiB string, so don't run it if we
        //      don't have enough RAM (the FreeBSD virtual machine we
        //      use on GitHub Actions has just 1GiB of RAM overall, and,
        //      if we run this test, the operating system just kills the
        //      executable).
        //
        std::ptrdiff_t      repetitions = 16'777'216 ;
        std::string const   piece =
                "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmno" ;
        std::ptrdiff_t const
                            final_string_size = piece.size() * repetitions ;
        auto const          min_ram_in_kib = static_cast< long long >(
            1.1 * static_cast< double >( final_string_size ) / 1024 ) ;
        if ( breeze::amount_of_physical_memory() >= min_ram_in_kib ) {

            std::string         s ;
            s.reserve( final_string_size ) ;
            for ( std::ptrdiff_t i = 0 ; i < repetitions ; ++ i ) {
                s += piece ;
            }
            breeze::sha384_hasher const
                                hasher( s.cbegin(), s.cend() ) ;
            BREEZE_CHECK( breeze::to_string( breeze::sha384_digest( hasher ) )
                == "5441235cc0235341ed806a64fb354742b5e5c02a3c5cb71b"
                   "5f63fb793458d8fdae599c8cd8884943c04f11b31b89f023" ) ;
        } else {
            std::cout << "(skipping one of the tests because this machine"
                " doesn't have enough RAM)" << std::endl ;
        }
    }
    {
        //      One million repetitions of 'a' ( [2] )
        //
        std::string const   one_million( 1000 * 1000, 'a' ) ;
        breeze::sha384_hasher const
                            hasher( one_million.cbegin(),
                                    one_million.cend() ) ;
        BREEZE_CHECK( breeze::to_string( breeze::sha384_digest( hasher ) )
            == "9d0e1809716474cb086e834e310a4a1ced149e9c00f24852"
               "7972cec5704c2a5b07b8b3dc38ecc4ebae97ddd87f3d8985" ) ;
    }
    {
        std::string const   s( "abcdefghbcdefghicdefghijdefghijkefghijklfghij"
                               "klmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlm"
                               "nopqrsmnopqrstnopqrstu" ) ; // [1]
        breeze::sha384_hasher const
                            hasher( s.cbegin(),
                                    s.cend() ) ;
        BREEZE_CHECK( breeze::to_string( breeze::sha384_digest( hasher ) )
            == "09330c33f71147e83d192fc782cd1b4753111b173b3b05d2"
               "2fa08086e3b0f712fcc7c71a557e2db966c3e9fa91746039" ) ;
    }
}

}

int
test_sha384()
{
    return breeze::test_runner::instance().run(
        "SHA-384",
        { check } ) ;
}
