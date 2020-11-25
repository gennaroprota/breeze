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
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
