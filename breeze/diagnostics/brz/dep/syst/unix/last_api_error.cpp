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

#include "breeze/iteration/begin_end.hpp"
#include <cerrno>
#include <string.h>
#include <string>

namespace breeze_ns {
namespace           {

char const          cant_obtain_description[] =
                            "<couldn't obtain the error description"
                            " (see the error code, instead)>" ;
char const          empty_error_description[] =
                            "<empty error description"
                            " (see the error code, instead)>" ;


//      strerror_message:
//      =================
//
//      To get an error description on a Unix system, the choice is
//      between strerror(), strerror_r() and strerror_l(). The first is
//      not (necessarily) thread-safe, so we exclude it. And
//      strerror_l(), which was introduced with POSIX.1-2008, is not
//      available (as of December 2020) on macOS. So, the only choice is
//      strerror_r().
//
//      Which, however, exists in two versions: a POSIX one and a GNU
//      one. The two versions have the same argument list but different
//      return types, so we use function overloading to handle either
//      version. That's the purpose of this class. (In the past, we
//      attempted to always get the POSIX version, but, on Ubuntu 16.04,
//      or with Clang 5.0.1 on Cygwin64, that requires undefining
//      _GNU_SOURCE, which breaks libstdc++ on Ubuntu 16.04, so it is a
//      no-no.)
// ---------------------------------------------------------------------------
class strerror_message
{
public:
    explicit            strerror_message( int error_code )
    {
        set_message( strerror_r( error_code, m_buffer, max_length ) ) ;
        * ( breeze::end( m_buffer ) - 1 ) = '\0' ;
    }

    //      Of course, on each system, only one of the two set_message()
    //      members of this class will be used. And this causes a
    //      -Wunused-member-function warning from Clang. Hence, the
    //      `#pragma`s.
    // -----------------------------------------------------------------------
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunused-member-function"
    // -----------------------------------------------------------------------

    void                set_message( int posix_return_value )
    {
        m_message = posix_return_value == 0
                        ? m_buffer[ 0 ] != '\0'
                            ? m_buffer
                            : empty_error_description
                        : cant_obtain_description
                        ;
    }

    void                set_message( char const * gnu_return_value )
    {
        //      Theoretically, the GNU variant cannot return a null
        //      pointer, but let's be cautious (it may return a pointer
        //      to an empty string, instead).
        // -------------------------------------------------------------------
        m_message = gnu_return_value != nullptr
                        ? gnu_return_value[ 0 ] != '\0'
                            ? gnu_return_value
                            : empty_error_description
                        : cant_obtain_description
                        ;
    }
#   pragma clang diagnostic pop

    char const *        message() const
    {
        return m_message ;
    }

private:
    static int const    max_length = 1024 ;
    char                m_buffer[ max_length + 1 ] ;
    char const *        m_message ;
} ;

std::string
format_message( char const * incipit, long long last_error )
{
    strerror_message const
                        sm( static_cast< int >( last_error ) ) ;
    char const * const  message = sm.message() ;

    return incipit != nullptr && incipit[ 0 ] != '\0'
        ? std::string( incipit ) + ": " + message
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
        m_code( error_code )
{
}

}
