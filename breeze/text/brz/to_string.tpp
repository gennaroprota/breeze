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

template< typename Period >
void
print_period( std::ostringstream & dest )
{
    dest << '[' ;
    dest << Period::type::num ;
    if ( Period::type::den != 1 ) {
        dest << '/' << Period::type::den ;
    }
    dest << "]s" ;
}

#define BREEZE_print_period( period, literal )              \
    template<>                                              \
    inline void                                             \
    print_period< period >( std::ostringstream & dest )     \
    {                                                       \
        dest << literal ;                                   \
    }                                                    /**/

BREEZE_print_period( std::pico,           "ps"  )
BREEZE_print_period( std::nano,           "ns"  )
BREEZE_print_period( std::micro,          "us"  )
BREEZE_print_period( std::milli,          "ms"  )
BREEZE_print_period( std::ratio< 1 >,     's'   )
BREEZE_print_period( std::ratio< 60 >,    "min" )
BREEZE_print_period( std::ratio< 3600 >,  'h'   )
BREEZE_print_period( std::ratio< 86400 >, 'd'   )

#undef BREEZE_print_period

template< typename OutputStreamable >
void
throw_on_failure( std::ostringstream const & ss )
{
    if ( ss.fail() ) {
        //      The output to the ostringstream may, in fact, only fail
        //      for an out of memory condition. In that case,
        //      readable_type_name() or the construction of the
        //      std::runtime_error might fail as well, but we try. In
        //      the worst case, we will throw a bad_alloc, anyway.
        // -------------------------------------------------------------------
        throw std::runtime_error( "error in to_string(), trying to convert"
                                  " an instance of " +
                                  readable_type_name< OutputStreamable >() ) ;
    }
}

}

template< typename T >
std::string
to_string( T const & object )
{
    return to_string_private::to_string_impl( object, 0 ) ;
}

template< typename Rep, typename Period >
std::string
to_string( std::chrono::duration< Rep, Period > d )
{
    using namespace to_string_private ;

    std::ostringstream  ss ;
    ss << d.count() ;
    print_period< typename Period::type >( ss ) ;

    throw_on_failure< decltype( d ) >( ss ) ;

    return ss.str() ;
}


template< typename OutputStreamable >
std::string
to_string( OutputStreamable const & object, std::locale const & loc )
{
    using namespace to_string_private ;

    std::ostringstream  ss ;
    ss.imbue( loc ) ;
    ss << object ;

    throw_on_failure< OutputStreamable >( ss ) ;

    return ss.str() ;
}

}

// Local Variables:
// mode: c++
// End:
// vim: set ft=cpp:
