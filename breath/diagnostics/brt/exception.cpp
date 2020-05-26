// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2015-2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/diagnostics/exception.hpp"
#include "breath/counting/signed_count.hpp"
#include <algorithm>
#include <cstddef>
#include <cstring>

namespace breath {

exception::exception() noexcept
    :   exception( "" )
{
}

exception::exception( std::string const & what_msg ) noexcept
{
    char const          incipit[] = "Breath library exception" ;

    std::strcpy( m_what_message, incipit ) ;

    if ( ! what_msg.empty() ) {
        char *              curr = &m_what_message[ 0 ] +
                                     ( signed_count( incipit ) - 1 ) ;
        char const          sep[] = ": " ;
        std::strcpy( curr, sep ) ;
        curr += ( signed_count( sep ) - 1 ) ;

        std::ptrdiff_t const
                            length_so_far = curr - &m_what_message[ 0 ] ;
        std::ptrdiff_t const
                            remaining_length = what_message_buffer_size - 1 -
                                                length_so_far ;
        std::ptrdiff_t const
                            length_to_copy = std::min< std::ptrdiff_t >(
                                                            what_msg.length(),
                                                            remaining_length ) ;

        std::strncpy( curr, what_msg.c_str(), length_to_copy ) ;
        curr[ length_to_copy ]  = '\0' ;
    }
}

char const *
exception::what() const noexcept
{
    return m_what_message ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
