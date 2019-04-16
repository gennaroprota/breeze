// ===========================================================================
//                        Copyright 2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/diagnostics/exception.hpp"
#include <iosfwd>

namespace breath {

class last_api_error
    :   public exception
{
public:
                        last_api_error() noexcept ;
                        last_api_error( char const * ) noexcept ;
                        last_api_error( last_api_error const & other ) noexcept ;
                        ~last_api_error() noexcept override ;
    int                 code() const noexcept ;
    virtual char const *
                        what() const noexcept override ;
    void                operator =( last_api_error const & ) = delete ;

private:
    friend std::ostream &
                    operator <<( std::ostream &, last_api_error const & ) ;

    int                 m_errno ;
    char                m_message[ 64 * 1024 ] ;
} ;

}
// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
