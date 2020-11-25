// ===========================================================================
//                     Copyright 2017-2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/porting/dependent_code.hpp"
#include BREEZE_DEPENDENT_CODE( compiler, readable_type_name.tpp )

#include "breeze/diagnostics/assert.hpp"
#include "breeze/text/trim_tail.hpp"

namespace breeze_ns {
namespace readable_type_name_private {

template< typename T >
class wrapper
{} ;

}

//      The use of the wrapper template, here, is to workaround the
//      following limitations of typeid( T ).name():
//
//      (1) if T is a reference to a possibly cv-qualified type, the
//      name returned is that of the cv-unqualified referenced type;
//      (2) if T is a cv-qualified type, the name returned is that of
//      the cv-unqualified type; furthermore, (3) if T is a class type
//      or a reference to a class type, the class shall be
//      completely-defined.
//
//      So, we take typeid( wrapper< T > ).name(), then remove
//      "wrapper" and its angle brackets. This gets rid of all three
//      limitations.
// ---------------------------------------------------------------------------
template< typename T >
std::string
readable_type_name()
{
    std::string const   wrapped_name =
        readable_type_name_private::demangled_typeid_name<
            readable_type_name_private::wrapper< T >
        >() ;

    auto const          begin_pos = wrapped_name.find(  '<' ) ;
    auto const          end_pos   = wrapped_name.rfind( '>' ) ;

    BREEZE_ASSERT( begin_pos < end_pos &&
                     end_pos != wrapped_name.npos ) ;

    //      Trim the tail of the string, in case T is itself a template
    //      instantiation. Something like e.g.
    //
    //        wrapper< my_template< int > >
    //
    //      yields:
    //
    //        "wrapper<my_template<int> >"
    //
    //      on all of Clang, GCC and MSVC.
    // -----------------------------------------------------------------------
    return breeze::trim_tail(
        wrapped_name.substr( begin_pos + 1, end_pos - begin_pos - 1 )
    ) ;
}

template< typename T >
std::string
readable_type_name( T const & ref )
{
    return readable_type_name_private::demangled_typeid_name( ref ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
