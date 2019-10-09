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
//
//      Tests the SHA-1 implementation with the test vectors which were
//      described at <http://www.nsrl.nist.gov/testdata/>. The relevant
//      documentation seems to be no longer available at nist.gov, but I
//      managed to recover it from the dbus project
//      (https://github.com/itemis/dbus), which has (or had) a copy: it
//      is the read_me in the nist_vectors/ subdirectory.
// ---------------------------------------------------------------------------

#include "breath/counting/count.hpp"
#include "breath/cryptography/digest.hpp"
#include "breath/cryptography/sha1_hasher.hpp"
#include "breath/diagnostics/assert.hpp"
#include "breath/environment/find_environment_string.hpp"
#include "breath/text/from_string.hpp"
#include "breath/text/to_string.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace {

class nist_file
{
    std::ifstream       m_stream ;

    template< typename T >
    friend nist_file &  operator >>( nist_file &, T & t ) ;

public:
    explicit            nist_file( char const * file_name ) ;
    bool                good() const ;
    bool                start_new_section() ;
} ;

nist_file::nist_file( char const * file_name )
{
    std::string const   breath_root( breath::find_environment_string(
                                                    "BREATH_ROOT" ).value() ) ;
    std::string const   subdir( breath_root +
                                   "/breath/cryptography/test/nist_vectors/" ) ;
    m_stream.open( ( subdir + file_name ).c_str() ) ;
    if ( ! m_stream.fail() ) {
        for ( std::string s ; s != "D>" ; ) {
            m_stream >> s ;
        }
    }

    if ( m_stream.fail() || m_stream.eof() ) {
        std::string const   what =
          std::string ( "cannot construct nist_file object for " ) + file_name ;

        throw std::ios::failure( what ) ;
    }
}

bool
nist_file::good() const
{
    return m_stream.good() ;
}

bool
nist_file::start_new_section()
{
    for ( std::string s ; s != "D>" && ! m_stream.fail() ; ) {
        m_stream >> s ;
    }

    return m_stream.good() ;
}

template< typename T >
nist_file &
operator >>( nist_file & f, T & t )
{
    f.m_stream >> t ;
    return f ;
}

class montecarlo_test
{
    breath::sha1_hasher m ;
    int                 m_count ;
    typedef breath::sha1_engine::word_type
                        word_type ;
    typedef breath::sha1_engine::byte_type
                        byte_type ; // gps esporre dall'hasher?
public:
                        montecarlo_test() : m_count( 0 )
                        {
                        }

    int                 get_count() const
    {
        return m_count ;
    }

    void                init( std::vector< byte_type > const & seed )
    {
        m.append( seed.cbegin(), seed.cend() ) ;
    }

    breath::sha1_digest next()
    {
        breath::sha1_digest result( m /* bogus argument */ ) ;
        word_type const     tot = 50 * 1000 ;
        for ( word_type i = 1 ; i <= tot ; ++ i ) {
            for ( byte_type a = 1 ; a <= m_count / 4 + 3 ; ++ a ) {
                m.push_back( 0 ) ;
            }

            m.push_back( static_cast< byte_type >( ( i >> 24 ) & 0xff ) ) ;
            m.push_back( static_cast< byte_type >( ( i >> 16 ) & 0xff ) ) ;
            m.push_back( static_cast< byte_type >( ( i >>  8 ) & 0xff ) ) ;
            m.push_back( static_cast< byte_type >( ( i       ) & 0xff ) ) ;

            // our "moral equivalent" of m = SHA1( m )
            result = breath::sha1_digest( m ) ;
            m = breath::sha1_hasher( result.begin(), result.end() ) ;
        }

        ++ m_count ;
        return result ;
    }
};

std::vector< breath::sha1_engine::byte_type >
read_compact_string( nist_file & messages, int z )
{
    typedef breath::sha1_engine::byte_type
                        byte_type ;

    bool                b ;
    messages >> b ;

    std::vector< byte_type >
                        msg ;
    byte_type           curr = 0 ;
    byte_type const     initial_mask = 128 ;
    byte_type           mask = initial_mask ;
    for ( int i = 0 ; i < z ; ++ i ) {
        unsigned            n ;
        messages >> n ;

        while ( n > 0 ) {
            if ( b ) {
                curr |= mask ;
            }

            mask /= 2 ;
            if ( mask == 0 ) {
                msg.push_back( curr ) , curr = 0, mask = initial_mask ;
            }

            -- n ;
        }

        b = ! b ;
    }

    return msg ;
}

}

bool
tests()
{
    using namespace breath ;

    nist_file           messages( "byte-messages.sha1" ) ;
    nist_file           hashes  ( "byte-hashes.sha1" ) ;

    int                 total = 0 ;
    int                 failed = 0 ;

    static struct
    {
        int                 section ;
        bool                pseudorandom ;
    } const             section_types[]
    = {
        { 0, false },
        { 1, false },
        { 2, true  }
    } ;

    std::size_t const   sections = breath::count( section_types ) ;

    std::string         calculated ;
    std::vector< breath::sha1_engine::byte_type >
                        msg ;
    montecarlo_test     montecarlo_harness ;

    for ( std::size_t sn = 0 ; sn < sections && hashes.good() ; /*++sn*/ ) {
        bool const          montecarlo_section = section_types[
                                                             sn ].pseudorandom ;
        if ( /*!montecarlo_section ||*/ montecarlo_harness.get_count() == 0 ) {
            // terminator found?
            //
            std::string         s ;
            messages >> s ;
            if ( s == "<D" ) {
                messages.start_new_section() ;
                hashes.start_new_section() ;
                ++ sn ;
                continue ;
            }

            int const           z( from_string< int >( s ) ) ;

            if ( montecarlo_section ) {
                msg = read_compact_string( messages, z ) ;
                BREATH_ASSERT( 8 * msg.size() == 416 ) ;

                montecarlo_harness.init( msg ) ;
            } else {
                msg = read_compact_string( messages, z ) ;
            }

            std::string         dummy ;
            messages >> dummy ; // skip terminator
        }

        std::string     expected ;
        hashes >> expected ;
        if ( expected == "<D" ) {
            break ; // done!
        }

        std::string     unused ;
        hashes >> unused ; // terminator

        if ( hashes.good() ) {
            ++ total ;
        }

        calculated = to_string(
            montecarlo_section
              ? montecarlo_harness.next()
              : make_digest( sha1_hasher( msg.begin(), msg.end() ) )
            ) ;

        if ( calculated != expected ) {
            ++ failed ;
            std::clog << "Failure on test vector # " << total << std::endl ;
            std::clog << "\tCalculated: " << calculated << std::endl ;
            std::clog << "\tExpected:   " << expected   << std::endl ;
        }
    }

    // report results
    //
    int const           expected_total = 329 ;
    int const           expected_pseudorandom_total = 100 ;
    bool const          all_used = total == expected_total &&
                 montecarlo_harness.get_count() == expected_pseudorandom_total ;
    bool const          test_passed = all_used && failed == 0 ;

    std::cout << "Total:  " << total  << " (of which "
              << montecarlo_harness.get_count() << " pseudorandom)" << '\n'
              << "Failed: " << failed << std::endl ;

    std::cout << ( all_used
                     ? "All vectors used"
                     : "Not all vectors used" )
              << std::endl ;

    std::cout << ( test_passed
                     ? "Test passed"
                     : "*** TEST FAILED ***" )
              << std::endl ;

    return test_passed ;
}

int
main()
try {
    return tests()
               ? EXIT_SUCCESS
               : EXIT_FAILURE
               ;
} catch ( std::exception const & ex ) {
    std::cerr << "Error: '" << ex.what() << '\'' << std::endl ;
    return EXIT_FAILURE ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
