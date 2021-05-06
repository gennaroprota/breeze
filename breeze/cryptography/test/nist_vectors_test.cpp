// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2006-2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//      Tests the SHA-1 implementation with the test vectors which were
//      described at <http://www.nsrl.nist.gov/testdata/>. The relevant
//      documentation seems to be no longer available at nist.gov, but I
//      managed to recover it from the dbus project
//      (https://github.com/itemis/dbus), which has (or had) a copy: it
//      is the read_me in the nist_vectors/ subdirectory.
// ---------------------------------------------------------------------------

#include "breeze/cryptography/sha1.hpp"
#include "breeze/environment/get_environment_variable.hpp"
#include "breeze/testing/testing.hpp"
#include "breeze/text/from_string.hpp"
#include "breeze/text/to_string.hpp"

#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <vector>

int                 test_nist_vectors() ;

namespace {

class nist_file
{
    std::ifstream       m_stream ;
    int                 m_section_number ;

    template< typename T >
    friend nist_file &  operator >>( nist_file &, T & t ) ;

public:
                        nist_file(  nist_file const & ) = delete ;
    nist_file &         operator =( nist_file const & ) = delete ;

    explicit            nist_file( std::string const & file_name ) ;
    bool                good() const ;
    int                 section_number() const ;

protected:
    bool                start_new_section() ;
} ;

nist_file::nist_file( std::string const & file_name )
    :   m_section_number( 0 )
{
    std::string const   breeze_root( breeze::get_environment_variable(
                                                    "BREEZE_ROOT" ).value() ) ;
    std::string const   subdir( breeze_root +
                                   "/breeze/cryptography/test/nist_vectors/" ) ;
    m_stream.open( ( subdir + file_name ).c_str() ) ;

    start_new_section() ;
    if ( ! good() ) {
        throw std::ios_base::failure(
            "cannot construct nist_file object for " + file_name ) ;
    }
}

bool
nist_file::good() const
{
    return m_stream.good() ;
}

int
nist_file::section_number() const
{
    return m_section_number ;
}

bool
nist_file::start_new_section()
{
    for ( std::string s ; s != "D>" && ! m_stream.fail() ; ) {
        m_stream >> s ;
    }

    if ( good() ) {
        ++ m_section_number ;
    }
    return good() ;
}

template< typename T >
nist_file &
operator >>( nist_file & f, T & t )
{
    f.m_stream >> t ;
    return f ;
}

class message_file
    :   public nist_file
{
public:
    explicit            message_file( std::string const & file_name ) ;
    std::vector< breeze::sha1_engine::byte_type >
                        next() ;

private:
    std::vector< breeze::sha1_engine::byte_type >
                        read_compact_string( int z ) ;
} ;

message_file::message_file( std::string const & file_name )
    :   nist_file( file_name )
{
}

std::vector< breeze::sha1_engine::byte_type >
message_file::next()
{
    std::vector< breeze::sha1_engine::byte_type >
                        result ;
    std::string         s ;
    *this >> s ;

    if ( good() ) {
        if ( s == "<D" ) {
            start_new_section() ;
            result = next() ;
        } else {
            result = read_compact_string(
                breeze::from_string< int >( s ).value() ) ;
            char                terminator ;
            *this >> terminator ;
        }
    }

    return result ;
}

std::vector< breeze::sha1_engine::byte_type >
message_file::read_compact_string( int z )
{
    typedef breeze::sha1_engine::byte_type
                        byte_type ;

    bool                b = false ;
    *this >> b ;

    std::vector< byte_type >
                        msg ;
    byte_type           curr = 0 ;
    byte_type const     initial_mask = 128 ;
    byte_type           mask = initial_mask ;
    for ( int i = 0 ; i < z ; ++ i ) {
        int                 n ;
        *this >> n ;

        while ( n > 0 ) {
            if ( b ) {
                curr |= mask ;
            }

            mask /= 2 ;
            if ( mask == 0 ) {
                msg.push_back( curr ) ;
                curr = 0 ;
                mask = initial_mask ;
            }

            -- n ;
        }

        b = ! b ;
    }

    return msg ;
}

class hash_file
    :   public nist_file
{
public:
    explicit            hash_file( std::string const & file_name ) ;
    std::string         next() ;
} ;

hash_file::hash_file( std::string const & file_name )
    :   nist_file( file_name )
{
}

std::string
hash_file::next()
{
    std::string         result ;
    *this >> result ;
    char                terminator ;
    *this >> terminator ;

    if ( good() && result == "<D" ) {
        start_new_section() ;
        result = next() ;
    }

    return result ;
}

class montecarlo_test
{
    breeze::sha1_hasher m ;
    int                 m_count ;
    typedef breeze::sha1_engine::word_type
                        word_type ;
    typedef breeze::sha1_engine::byte_type
                        byte_type ; // gps esporre dall'hasher?
public:
                        montecarlo_test() : m_count( 0 )
                        {
                        }

    int                 count() const
    {
        return m_count ;
    }

    void                init( std::vector< byte_type > const & seed )
    {
        m.append( seed.cbegin(), seed.cend() ) ;
    }

    breeze::sha1_digest next()
    {
        breeze::sha1_digest result( m /* bogus argument */ ) ;
        word_type const     tot = 50 * 1000 ;
        for ( word_type i = 1 ; i <= tot ; ++ i ) {
            for ( int a = 1 ; a <= m_count / 4 + 3 ; ++ a ) {
                m.append( 0 ) ;
            }

            m.append( static_cast< byte_type >( ( i >> 24 ) & 0xff ) ) ;
            m.append( static_cast< byte_type >( ( i >> 16 ) & 0xff ) ) ;
            m.append( static_cast< byte_type >( ( i >>  8 ) & 0xff ) ) ;
            m.append( static_cast< byte_type >( ( i       ) & 0xff ) ) ;

            // our "moral equivalent" of m = SHA1( m )
            result = breeze::sha1_digest( m ) ;
            m = breeze::sha1_hasher( result.begin(), result.end() ) ;
        }

        ++ m_count ;
        return result ;
    }
} ;

void
report_results( int total, int failed, int pseudo_random_total )
{
    int const           expected_total = 329 ;
    int const           expected_pseudo_random_total = 100 ;
    bool const          all_used = total == expected_total &&
                pseudo_random_total == expected_pseudo_random_total ;
    bool const          test_passed = all_used && failed == 0 ;

    std::cout << "Total:  " << total  << " (of which "
              << pseudo_random_total << " pseudo-random)" << '\n'
              << "Failed: " << failed << std::endl ;

    std::cout << ( all_used
                     ? "All vectors used"
                     : "Not all vectors used" )
              << std::endl ;

    std::cout << ( test_passed
                     ? "Test passed"
                     : "*** TEST FAILED ***" )
              << std::endl ;
}

void
do_test()
{
    using namespace breeze ;
    message_file        messages( "byte-messages.sha1" ) ;
    hash_file           hashes(   "byte-hashes.sha1"   ) ;

    int                 total = 0 ;
    int                 failed = 0 ;

    static struct
    {
        bool                pseudo_random ;
    } const             section_types[]
    = {
        { false },
        { false },
        { true  }
    } ;

    montecarlo_test     montecarlo_harness ;
    std::string         expected = hashes.next() ;
    while ( hashes.good() ) {
        ++ total ;
        std::vector< sha1_engine::byte_type >
                            msg = messages.next() ;
        bool const          is_montecarlo_section =
            section_types[ messages.section_number() - 1 ].pseudo_random ;

        if ( is_montecarlo_section && montecarlo_harness.count() == 0 ) {
            montecarlo_harness.init( msg ) ;
        }

        std::string const   calculated = to_string(
                is_montecarlo_section
                    ? montecarlo_harness.next()
                    : make_digest( sha1_hasher( msg.begin(), msg.end() ) )
            ) ;

        if ( calculated != expected ) {
            ++ failed ;
            std::cerr << "Failure on test vector # " << total << std::endl ;
            std::cerr << "\tCalculated: " << calculated << std::endl ;
            std::cerr << "\tExpected:   " << expected   << std::endl ;

            BREEZE_CHECK( false ) ;
        }

        expected = hashes.next() ;
    }

    report_results( total, failed, montecarlo_harness.count() ) ;
}

}

int
test_nist_vectors()
{
    return breeze::test_runner::instance().run(
        "NIST vectors",
        { do_test } ) ;
}
