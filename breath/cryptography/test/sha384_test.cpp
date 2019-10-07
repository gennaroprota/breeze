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

#include "breath/cryptography/sha384_hasher.hpp"
#include "breath/cryptography/digest.hpp"
#include "breath/text/to_string.hpp"
#include "breath/testing/testing.hpp"

#include <iostream>
#include <ostream>
#include <string>

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
        breath::sha384_hasher const
                            hasher( s.cbegin(), s.cend() ) ;
        BREATH_CHECK( breath::to_string( breath::sha384_digest( hasher ) )
            == "38b060a751ac96384cd9327eb1b1e36a21fdb71114be0743"
               "4c0cc7bf63f6e1da274edebfe76f65fbd51ad2f14898b95b" ) ;
    }
    {
        std::string const   s( "abc" ) ; // [1]
        breath::sha384_hasher const
                            hasher( s.cbegin(), s.cend() ) ;
        BREATH_CHECK( breath::to_string( breath::sha384_digest( hasher ) )
            == "cb00753f45a35e8bb5a03d699ac65007272c32ab0eded163"
               "1a8b605a43ff5bed8086072ba1e7cc2358baeca134c825a7" ) ;
    }
    {
        //      16,777,216 repetitions of 'piece' ( [2] )
        //
        std::string const   piece =
            "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmno" ;
        std::string         s ;
        for ( std::size_t i = 0 ; i < 16'777'216 ; ++ i ) {
            s += piece ;
        }
        breath::sha384_hasher const
                            hasher( s.cbegin(), s.cend() ) ;
        BREATH_CHECK( breath::to_string( breath::sha384_digest( hasher ) )
            == "5441235cc0235341ed806a64fb354742b5e5c02a3c5cb71b"
               "5f63fb793458d8fdae599c8cd8884943c04f11b31b89f023" ) ;
    }
    {
        //      One million repetitions of 'a' ( [2] )
        //
        std::string const   one_million( 1000 * 1000, 'a' ) ;
        breath::sha384_hasher const
                            hasher( one_million.cbegin(),
                                    one_million.cend() ) ;
        BREATH_CHECK( breath::to_string( breath::sha384_digest( hasher ) )
            == "9d0e1809716474cb086e834e310a4a1ced149e9c00f24852"
               "7972cec5704c2a5b07b8b3dc38ecc4ebae97ddd87f3d8985" ) ;
    }
    {
        std::string const   s( "abcdefghbcdefghicdefghijdefghijkefghijklfghij"
                               "klmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlm"
                               "nopqrsmnopqrstnopqrstu" ) ; // [1]
        breath::sha384_hasher const
                            hasher( s.cbegin(),
                                    s.cend() ) ;
        BREATH_CHECK( breath::to_string( breath::sha384_digest( hasher ) )
            == "09330c33f71147e83d192fc782cd1b4753111b173b3b05d2"
               "2fa08086e3b0f712fcc7c71a557e2db966c3e9fa91746039" ) ;
    }
}

int
main()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    return test_runner::instance().run( { check } ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
