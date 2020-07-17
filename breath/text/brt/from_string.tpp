// ===========================================================================
//                     Copyright 2016-2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include <istream>
#include <sstream>
#include <utility>

namespace breath_ns {

template< typename T >
maybe< T >
from_string( std::string const & s )
{
    T                   t ;
    std::istringstream  ss( s ) ;

    return ( ss >> t ) && ( ss >> std::ws ).eof()
        ? maybe< T >( std::move( t ) )
        : maybe< T >()
        ;
}

template<>
inline maybe< std::string >
from_string< std::string >( std::string const & s )
{
    return maybe< std::string >( s ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
