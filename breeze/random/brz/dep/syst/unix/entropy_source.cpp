// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2008 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//      Implementation for systems that have /dev/random (Unix).
// ---------------------------------------------------------------------------

#include "breeze/random/entropy_source.hpp"
#include "breeze/counting/signed_count.hpp"
#include "breeze/diagnostics/assert.hpp"

#include <cstddef>
#include <cstdio>
#include <limits>

namespace breeze_ns {

class entropy_source::impl
{
public:
                        impl(       impl const & ) = delete ;
    impl &              operator =( impl const & ) = delete ;

                        impl() ;
                        ~impl() noexcept ;
    bool                release() noexcept ;
    result_type         next() ;

private:
    bool                is_open() const noexcept ;
    void                to_buffer( unsigned char /*gps*/ * buffer,
                                   std::ptrdiff_t count ) ;

private:
    FILE *              m_file ;
} ;

entropy_source::impl::impl()
    :   m_file( std::fopen( "/dev/random", "rb" ) )
{
    if ( ! is_open() ) {
        entropy_source::exception::raise( "cannot open /dev/random" ) ;
    }

    //      Attempt to turn off the library-level buffering. If that
    //      fails we ignore the failure.
    //
    //      (If the need arises to verify this, I might store the
    //      information given by setvbuf()'s return value and add an
    //      is_buffered() member function.)
    // -----------------------------------------------------------------------
    std::setvbuf( m_file, nullptr, _IONBF, 0 ) ;
}

entropy_source::impl::~impl() noexcept
{
    release() ;
}

entropy_source::result_type
entropy_source::impl::next()
{
    BREEZE_ASSERT( is_open() ) ;

    unsigned char       buffer[ 1 ] ;
    to_buffer( &buffer[ 0 ], breeze::signed_count( buffer ) ) ;
    return buffer[ 0 ] ;
}

bool
entropy_source::impl::is_open() const noexcept
{
    return m_file != nullptr ;
}

void
entropy_source::impl::to_buffer( unsigned char /*gps*/ * buffer,
                                 std::ptrdiff_t count )
{
    BREEZE_ASSERT( count >= 0 ) ;

    std::size_t const   read =
        std::fread( buffer, sizeof buffer[ 0 ], count, m_file ) ;

    if ( read < static_cast< std::size_t >( count ) ) {
        exception::raise( "entropy_source: not enough bytes" ) ;
    }
}

bool
entropy_source::impl::release() noexcept
{
    //      Close is attempted ONCE. Postcondition: is_open() == false,
    //      regardless.
    // -----------------------------------------------------------------------
    bool            success = false ;
    if ( is_open() ) {
        success = std::fclose( m_file ) == 0 ;
        m_file = nullptr ;
    }
    return success ;
}

[[ noreturn ]] void
entropy_source::exception::raise( std::string const & message )
{
    throw entropy_source::exception( "Breeze entropy_source: " + message ) ;
}

}
