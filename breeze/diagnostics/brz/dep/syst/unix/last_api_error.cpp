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
#include <locale.h>
#include <string.h>
#include <string>

namespace breeze_ns {
namespace           {

std::string
format_message( char const * incipit, long long last_error )
{
    static char const   cant_obtain_description[] =
                            "couldn't obtain the error description"
                            "; see the error code, instead" ;

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
        description = strerror_l( static_cast< int >( last_error ), locale ) ;
        freelocale( locale ) ;
    }

    char const * const  message = description != nullptr
                                      ? description
                                      : &cant_obtain_description[ 0 ]
                                      ;
    return incipit != nullptr && incipit[ 0 ] != '\0'
        ? std::string( incipit) + ": " + message
        : message
        ;
}

}

//      A comment similar to the one in the Windows implementation file
//      holds, here. The system function which formats the error message
//      may fail and set errno itself. So we need to protect from that
//      case.
//
//      For this reason, we forward to another (private) constructor.
// ---------------------------------------------------------------------------
last_api_error::last_api_error( char const * p )
    :   last_api_error( p, errno )
{
}

last_api_error::last_api_error( char const * p, long long error_code )
    :   base_type( format_message( p, error_code ) ),
        m_last_error( error_code )
{
}

long long
last_api_error::code() const noexcept
{
    return m_last_error ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
