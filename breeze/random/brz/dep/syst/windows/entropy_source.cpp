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

#include "breeze/random/entropy_source.hpp"
#include "breeze/diagnostics/assert.hpp"
#include "breeze/diagnostics/last_api_error.hpp"

#include <Windows.h>
#include <wincrypt.h>

#include <string>
#include <vector>

namespace breeze_ns {

class entropy_source::impl
{
public:
                        impl(       impl const & ) = delete ;
    impl &              operator =( impl const & ) = delete ;

private:
    HCRYPTPROV          m_provider_handle ;
    bool                m_handle_is_valid ;

public:
                        impl() ;
                        ~impl() noexcept ;

    result_type         next() ;
    bool                release() noexcept ;

private:
    bool                acquire( DWORD flags = 0 ) ;
    bool                is_released() const noexcept ;
    void                to_buffer( unsigned char * buffer,
                                   int count ) ;
} ;

entropy_source::impl::impl()
    // note: m_handle_is_valid intentionally not initialized here---see below
{
    if ( ! acquire() ) {
        entropy_source::exception::raise( "cannot acquire the HCRYPTPROV handle"
                                        ) ;
    }
    //      Note that this member is intentionally not initialized in
    //      the ctor initializer list; in case of exceptions there is
    //      no way it could be used.
    // -----------------------------------------------------------------------
    m_handle_is_valid = true ;
}

bool
entropy_source::impl::acquire( DWORD flags )
{
    return CryptAcquireContextA( &m_provider_handle,
                                 nullptr,
                                 nullptr,
                                 PROV_RSA_FULL,
                                 flags | CRYPT_VERIFYCONTEXT ) != 0 ;
}

bool
entropy_source::impl::is_released() const noexcept
{
    return ! m_handle_is_valid ;
}

//      This release could be attempted more than once? This is
//      different from Unix! --gps
// ---------------------------------------------------------------------------
bool
entropy_source::impl::release() noexcept
{
    bool                success = false ;
    if ( ! is_released() ) {
        success = CryptReleaseContext( m_provider_handle,
                                       0 // this is reserved (future use) and
                                         // must be zero
                                     ) != 0 ;
        m_handle_is_valid = ! success ;
    }
    return success ;
}

void
entropy_source::impl::to_buffer( unsigned char * buffer, int count )
{
    BREEZE_ASSERT( count >= 0 ) ;

    if ( count > 0 ) {

        int const           r = CryptGenRandom( m_provider_handle,
                                                static_cast< DWORD >( count ),
                                                buffer ) ;
        if ( r == 0 ) {
            entropy_source::exception::raise(
                                        "cannot generate random numbers" ) ;
        }
    }
}

entropy_source::result_type
entropy_source::impl::next()
{
    BREEZE_ASSERT( ! is_released() ) ;

    unsigned char       c ;
    to_buffer( &c, sizeof c ) ;
    return c ;
}

entropy_source::impl::~impl() noexcept
{
    release() ;
}

[[ noreturn ]] void
entropy_source::exception::raise( std::string const & message )
{
    std::string const   s = "Breeze entropy_source: " +
                                        message + " - " ;
    last_api_error const
                        err( s.c_str() ) ;

    throw entropy_source::exception( err.what() ) ;
}

}
