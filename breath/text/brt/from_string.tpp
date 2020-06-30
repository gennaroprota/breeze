// ===========================================================================
//                     Copyright 2016-2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/diagnostics/exception.hpp"
#include "breath/type_identification/readable_type_name.hpp"

#include <istream>
#include <sstream>

namespace breath_ns {

template< typename T >
T
from_string( std::string const & s )
{
    T                   t ;
    std::istringstream  ss( s ) ;
    if ( ! ( ss >> t ) || ! ( ss >> std::ws ).eof() ) {
        throw breath::exception( "error in from_string(), trying to"
                                 " convert \"" + s + "\" to the type " +
                                 readable_type_name< T >() ) ;
    }
    return t ;
}

template<>
inline std::string
from_string< std::string >( std::string const & s )
{
    return s ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
