// ===========================================================================
//                     Copyright 2017-2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//      Implementation helper for readable_type_name() for Visual C++.
// -------------------------------------------------------------------------

#include <typeinfo>

namespace breath {
namespace readable_type_name_private {

template< typename T >
std::string
demangled_typeid_name()
{
    return typeid( T ).name() ;
}

}
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
