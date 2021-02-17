// ===========================================================================
//                     Copyright 2008-2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/type_identification/readable_type_name.hpp"
#include <sstream>
#include <stdexcept>

namespace breeze_ns {
namespace to_string_private {

template< typename T >
auto
to_string_impl( T const & object, int ) -> decltype( object.to_string() )
{
    return object.to_string() ;
}

template< typename T >
std::string
to_string_impl( T const & object, ... )
{
    return breeze::to_string( object, std::locale() ) ;
}

}

template< typename T >
std::string
to_string( T const & object )
{
    return to_string_private::to_string_impl( object, 0 ) ;
}

template< typename OutputStreamable >
std::string
to_string( OutputStreamable const & object, std::locale const & loc )
{
    std::ostringstream  ss ;
    ss.imbue( loc ) ;
    ss << object ;
    if ( ss.fail() ) {
        throw std::runtime_error( "error in to_string(), trying to convert"
                                  " an instance of " +
                                  readable_type_name< OutputStreamable >() ) ;
    }
    return ss.str() ;
}

}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
