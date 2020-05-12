// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include <cerrno>
#include <ostream>
#include <locale.h>
#include <string.h>

namespace breath {

last_api_error::last_api_error( char const * p ) noexcept
    :   m_last_error( errno )
{
    static char const   cant_obtain_description[] =
                            "can't obtain the error description"
                            ": see the error code, instead" ;

    //! \todo
    //! Most of this code is duplicated with the Windows variant.
    //! How to put it in common? --gps
    //
    int const           max_incipit_size = 512 ;
    static_assert( max_incipit_size < ( sizeof m_message / 10 ), "" ) ;

    if ( p != nullptr ) {
        strncpy( m_message, p, max_incipit_size ) ;

        std::size_t const   len = strlen( p ) ;

        char const          sep[] = ": " ;
        if ( len != 0 ) {
            strcpy( m_message + len, sep ) ;
        }
    }

    std::size_t const   offset = p == nullptr
                                    ? 0
                                    : strlen( m_message )
                                    ;

    //      We use strerror_l(), here, although that was introduced only
    //      with POSIX.1-2008.
    //
    //      Here's the reason:
    //
    //      the choice is between strerror(), strerror_r() and
    //      strerror_l(). The first is not thread-safe, so is
    //      immediately excluded. strerror_r() exists in two variants: a
    //      POSIX one and a GNU one, and getting the POSIX version on
    //      Ubuntu 16.04, or with Clang 5.0.1 on Cygwin64, requires
    //      undefining _GNU_SOURCE; this undefine, though, breaks
    //      libstdc++ on Ubuntu (again, this occurred on 16.04), so it
    //      is a no-no.
    //
    //      Thus, we are left with GNU's _r() variant and the _l() one.
    //      For portability, of course, we prefer the latter (which is
    //      even recommended by POSIX itself:
    //
    //        <http://austingroupbugs.net/view.php?id=655>
    //
    //      ).
    //
    //      Note that this means we have to give up on Mac OS X, as that
    //      doesn't support POSIX.1-2008 (nor, of course, it supports
    //      the GNU strerror_r()). It might be supported in the future,
    //      though (we hope).
    // -----------------------------------------------------------------------
    char const *        description = nullptr ;
    locale_t const      locale = newlocale( LC_MESSAGES_MASK, "", locale_t() ) ;

    if ( locale != locale_t() ) {
        description = strerror_l( static_cast< int >( m_last_error ), locale ) ;
        freelocale( locale ) ;
    }

    char const * const  message = description != nullptr
                                      ? description
                                      : &cant_obtain_description[ 0 ]
                                      ;
    strncpy( m_message + offset, message, sizeof m_message - offset - 1 ) ;
    m_message[ sizeof m_message - 1 ] = '\0' ;
}

last_api_error::last_api_error( last_api_error const & other ) noexcept
    :   exception( other ),
        m_last_error( other.m_last_error )
{
    strcpy( &m_message[ 0 ], &other.m_message[ 0 ] ) ;
}

last_api_error::~last_api_error() noexcept
{
}

long long
last_api_error::code() const noexcept
{
    return m_last_error ;
}

char const *
last_api_error::what() const noexcept
{
    return m_message ;
}

std::ostream &
operator <<( std::ostream & dest, last_api_error const & last )
{
    return dest << last.m_message << " [code: " << last.code() << ']' ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
