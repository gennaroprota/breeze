// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//                         Copyright 2004 James Kanze
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/stream/inserter.hpp"
#include "breeze/diagnostics/assert.hpp"
#include <algorithm>
#include <cstdio> // for EOF
#include <cstring>

namespace breeze_ns {

inserter::inserter( std::ostream & dest, width_reset wr )
    :   m_dest( dest ),
        m_sentry( dest ),
        m_reset_width( wr == reset_width )
{
}

inserter::~inserter() noexcept
{
    if ( m_reset_width && sentry_is_ok() ) {
        m_dest.width( 0 ) ;
    }
}

bool
inserter::sentry_is_ok() const noexcept
{
    return static_cast< bool >( m_sentry ) ;
}

void
inserter::put( char c )
{
    BREEZE_ASSERT( sentry_is_ok() ) ;

    if ( m_dest && m_dest.rdbuf()->sputc( c ) == EOF ) {
        m_dest.setstate( std::ios::badbit ) ;
    }
}

void
inserter::put( char const * source, std::streamsize count )
{
    BREEZE_ASSERT( sentry_is_ok() ) ;
    BREEZE_ASSERT( count >= 0 ) ;

    if ( m_dest && m_dest.rdbuf()->sputn( source, count ) != count ) {
        m_dest.setstate( std::ios::badbit ) ;
    }
}

void
inserter::pad( std::streamsize count )
{
    if ( m_dest && count > 0 ) {
        std::streamsize const
                            buf_size = 100 ;
        char                buffer[ buf_size ] ;
        std::memset( buffer, m_dest.fill(), sizeof buffer ) ;
        do {
            auto const          n = std::min( buf_size, count ) ;
            put( buffer, n ) ;
            count -= n ;
        } while ( m_dest && count > 0 ) ;
    }
}

}
