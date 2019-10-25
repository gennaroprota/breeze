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
//      Implementation for systems that have /dev/random (Unix)
// ---------------------------------------------------------------------------

#include "breath/random/entropy_source.hpp"
#include "breath/counting/count.hpp"
#include "breath/diagnostics/assert.hpp"
#include "breath/idiom/declare_non_copyable.hpp"
#include "breath/random/subrange_max.hpp"

#include <cstddef>
#include <cstdio>
#include <limits>

namespace breath {

class entropy_source::impl
{
    BREATH_DECLARE_NON_COPYABLE( impl )

public:
                        impl() ;
                        ~impl() noexcept ;
    bool                release() noexcept ;
    result_type         next() ;
    result_type         minimum() const noexcept ;
    result_type         maximum() const noexcept ;

private:
    bool                is_open() const noexcept ;
    void                to_buffer( unsigned char /*gps*/ * buffer, std::ptrdiff_t count ) noexcept ;

private:
    FILE *              m_file ;
} ;

entropy_source::impl::impl()
    : m_file( std::fopen( "/dev/random", "rb" ) )
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
    BREATH_ASSERT( is_open() ) ;

    unsigned char       buffer[ 1 ] ;
    to_buffer( &buffer[ 0 ], breath::count( buffer ) ) ;
    return buffer[ 0 ] ;
}

entropy_source::result_type
entropy_source::impl::minimum() const noexcept
{
    return 0 ;
}

entropy_source::result_type
entropy_source::impl::maximum() const noexcept
{
    return 255 ;
}

bool
entropy_source::impl::is_open() const noexcept
{
    return m_file != nullptr ;
}

void
entropy_source::impl::to_buffer( unsigned char /*gps*/ * buffer, std::ptrdiff_t count ) noexcept
{
    BREATH_ASSERT( count >= 0 ) ;

    auto const          read =
        std::fread( buffer, sizeof buffer[ 0 ], count, m_file ) ;

    if ( read < count ) {
        exception::raise( "not enough bytes" ) ;
    }

}

bool
entropy_source::impl::release() noexcept
{
    // Close is attempted ONCE. Postcondition: is_open() == false, regardless.

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
    throw entropy_source::exception( "Breath entropy_source: " + message ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
