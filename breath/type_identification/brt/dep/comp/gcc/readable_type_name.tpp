// ===========================================================================
//                     Copyright 2017-2018 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//      Implementation helpers for readable_type_name() for GCC.
// ---------------------------------------------------------------------------

#include <cstdlib>
#include <cxxabi.h>
#include <stdexcept>
#include <string>
#include <typeinfo>

namespace breath_ns {
namespace readable_type_name_private {

std::string         demangle( std::string const & name ) ;

inline std::string
demangle( char const * name )
{
    class deallocator
    {
    public:
        explicit deallocator( char * p )
            :   m_p( p )
        {
        }
        ~deallocator()
        {
            std::free( m_p ) ;
        }
    private:
        char * const    m_p ;
    } ;

    //      The __cxa_demangle() specification can be found at:
    //
    //        <https://itanium-cxx-abi.github.io/cxx-abi/abi.html>.
    //
    //      Note that we pass nullptr for the last parameter, which *is*
    //      supported by libstdc++; this was clarified by Jonathan
    //      Wakely with this commit:
    //
    //        <https://gcc.gnu.org/r264127>.
    // -----------------------------------------------------------------------
    char * const        p = abi::__cxa_demangle( name,
                                                 nullptr,
                                                 nullptr,
                                                 nullptr ) ;
    if ( p == nullptr ) {
        throw std::runtime_error( "__cxa_demangle() failed to demangle \"" +
                                  std::string( name ) + "\"" ) ;
    }

    deallocator const   dlc( p ) ;

    return std::string( p ) ;
}

template< typename T >
std::string
demangled_typeid_name()
{
    return demangle( typeid( T ).name() ) ;
}

template< typename T >
std::string
demangled_typeid_name( T const & ref )
{
    return demangle( typeid( ref ).name() ) ;
}

}
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
