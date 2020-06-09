// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2006 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/counting/signed_count.hpp"
#include "breath/cryptography/digest.hpp"
#include "breath/cryptography/md5_hasher.hpp"
#include "breath/cryptography/sha1_hasher.hpp"
#include "breath/cryptography/sha224_hasher.hpp"
#include "breath/cryptography/sha256_hasher.hpp"
#include "breath/cryptography/sha512_hasher.hpp"
#include "breath/iteration/begin_end.hpp"
#include "breath/testing/testing.hpp"
#include "breath/text/to_string.hpp"

#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>

int                 test_merkle_damgard_hashing() ;

namespace {

std::string::size_type const
                    million( 1000 * 1000 );
std::string const   one_million_a( million, 'a' );

template< typename Hasher >
class test_vectors
{
public:
    struct test_entry
    {
        test_entry( std::string const & s, std::string const & e, int r = 0 )
            :   source( s ), expected( e ), repetitions( r )
        {
        } 

        std::string         source ;
        std::string         expected ;
        int                 repetitions ;
    } ;

    static test_entry const
                        entries[] ;
};

//      MD5 test vectors
// ---------------------------------------------------------------------------
template<>
test_vectors< breath::md5_hasher >::test_entry const
    test_vectors< breath::md5_hasher >::entries[] =
{
    // test cases from RFC 1321
    {                           "" ,  "d41d8cd98f00b204e9800998ecf8427e" },
    {                          "a" ,  "0cc175b9c0f1b6a831c399e269772661" },
    {                        "abc" ,  "900150983cd24fb0d6963f7d28e17f72" },
    {             "message digest" ,  "f96b697d7cb7938d525a2f31aaf161d0" },
    { "abcdefghijklmnopqrstuvwxyz" ,  "c3fcd3d76192e4007dfb496cca67e13b" },

    { "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
                        "0123456789" ,  "d174ab98d277d9f5a5611c2c9f419d9f" },

    { "12345678901234567890123456"
        "78901234567890123456789012"
        "34567890123456789012345678"
                                "90" ,  "57edf4a22be3c955ac49da2e2107b67a" },

    // other test cases
    {                     "Breeze" ,  "a35715e7a6549f47dc766f75a0b1088c" },

    { "The quick brown fox jumps "
                "over the lazy dog" ,  "9e107d9d372bb6826bd81d3542a419d6" },

    { "The quick brown fox jumps "
                "over the lazy cog" ,  "1055d3e698d289f2af8663725127bd4b" },

    // 56 byte (= 448 bit) message
    { "01234567890123456789012345"
        "67890123456789012345678901"
        "2345"                       ,  "8af270b2847610e742b0791b53648c09" },

    // 57-byte
    { "01234567890123456789012345"
        "67890123456789012345678901"
        "23456"                      ,  "c620bace4cde41bc45a14cfa62ee3487" },

    // 64-byte
    { "01234567890123456789012345"
        "67890123456789012345678901"
        "234567890123"               ,  "7f7bfd348709deeaace19e3f535f8c54" }
} ;


//      SHA-1 test vectors
// ---------------------------------------------------------------------------
template<>
test_vectors< breath::sha1_hasher >::test_entry const
    test_vectors< breath::sha1_hasher >::entries[] =
{
    // test cases from FIPS 180-2 with change notice
    { "abc", "a9993e364706816aba3e25717850c26c9cd0d89d"},

    { "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
        "84983e441c3bd26ebaae4aa1f95129e5e54670f1" },
    { one_million_a,
        "34aa973cd4c4daa4f61eeb2bdbad27316534016f" },

    // the usual "lazy cog" :-)
    { "The quick brown fox jumps over the lazy cog",
        "de9f2c7fd25e1b3afad3e85a0bd17d9b100db4b3" }
} ;

//      SHA-256 test vectors
// ---------------------------------------------------------------------------
template<>
test_vectors< breath::sha256_hasher >::test_entry const
    test_vectors< breath::sha256_hasher >::entries[] =
{
    // test cases from FIPS
    { "abc",
        "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad" },
    { "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
        "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1" },
    { one_million_a,
        "cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0" },

    // others

    // 2^(10+19) = 2^29 bytes = 2^32 bits
    { std::string( 1ul << 10, 'a' ),
        "b9045a713caed5dff3d3b783e98d1ce5778d8bc331ee4119d707072312af06a7",
        ( 1ul << 19 ) - 1 }
} ;

//      SHA-224 test vectors
// ---------------------------------------------------------------------------
template<>
test_vectors< breath::sha224_hasher >::test_entry const
    test_vectors< breath::sha224_hasher >::entries[] =
{
    // from FIPS
    { "abc",
        "23097d223405d8228642a477bda255b32aadbce4bda0b3f7e36c9da7" }
} ;


//      SHA-512 test vectors
// ---------------------------------------------------------------------------
template<>
test_vectors< breath::sha512_hasher >::test_entry const
    test_vectors< breath::sha512_hasher >::entries[] =
{
    // from FIPS
    { "abc",
        "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a"
        "2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f" },

    { "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmn"
        "hijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu",

        "8e959b75dae313da8cf4f72814fc143f8f7779c6eb9f7fa17299aeadb6889018"
        "501d289e4900f7e4331b99dec4b5433ac7d329eeb6dd26545e96e55b874be909" },

    { one_million_a,
        "e718483d0ce769644e2e42c7bc15b4638e1f98b13b2044285632a803afa973eb"
        "de0ff244877ea60a4cb0432ce577c31beb009c5c2c49aa2e4eadb217ad8cc09b"}
} ;

}


//      Smoke test - Check against a list of known digests.
// ---------------------------------------------------------------------------
template< typename Hasher >
void check_known_digests()
{
    typedef std::string string_type ;
    typedef test_vectors< Hasher >
                        known ;

    for ( std::ptrdiff_t i = 0 ; i < breath::signed_count( known::entries ) ;
                                                                        ++ i ) {

        using breath::digest ;

        typename known::test_entry const &
                            entry( known::entries[ i ] ) ;
        string_type const & src( entry.source ) ;

        Hasher              hasher( src.cbegin(), src.cend() ) ;

        for ( int r = 0 ; r < entry.repetitions ; ++ r ) {
            hasher.append( src.cbegin(), src.cend() ) ;
        }

        digest< Hasher > const
                            d( hasher ) ;
        std::string const   result = breath::to_string( d ) ;
        BREATH_CHECK( result == entry.expected ) ;
    }
}

int
test_merkle_damgard_hashing()
{
    using namespace breath ;

    console_reporter    cr( std::cout ) ;
    test_runner::instance().attach_reporter( cr ) ;

    test_descriptor const
                        desc[] =
    {
        check_known_digests< breath::   md5_hasher > ,
        check_known_digests< breath::  sha1_hasher > ,
        check_known_digests< breath::sha256_hasher > ,
        check_known_digests< breath::sha224_hasher > ,
        check_known_digests< breath::sha512_hasher >
    } ;

    return test_runner::instance().run( cbegin( desc ), cend( desc) ) ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
