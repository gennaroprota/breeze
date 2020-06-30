// ===========================================================================
//                        Copyright 2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

namespace breath_ns {

template< typename T >
program_option_with_value< T >::program_option_with_value(
                                                      std::string const & name,
                                                      char short_name,
                                                      bool mandatory,
                                                      T const & def,
                                                      std::string const & desc,
                                            option_reader< T > const & reader )
    :   m_name( name ), m_short_name( short_name ), m_is_mandatory( mandatory ),
        m_is_set( false ), m_default_value( def ), m_actual_value( def ),
        m_reader( reader )
{
    m_description = full_description( desc ) ;
    command_line::instance().add( *this ) ;
}

template< typename T >
T const &
program_option_with_value< T >::get() const
{
    return m_actual_value ;
}

template< typename T>
bool
program_option_with_value< T >::has_value() const
{
    return true ;
}

template< typename T >
bool
program_option_with_value< T >::set()
{
    return false ;
}

template< typename T >
bool
program_option_with_value< T >::set( std::string const & value )
{
    try {
        m_actual_value = read( value ) ;
        m_is_set = true ;
    } catch( std::exception const & ) {
            return false;
    }
    return true;
}

template< typename T >
bool
program_option_with_value< T >::is_set() const
{
    return m_is_set ;
}

template< typename T >
bool
program_option_with_value< T >::is_valid() const
{
    return ! m_is_mandatory || m_is_set ;
}

template< typename T >
bool
program_option_with_value< T >::is_mandatory() const
{
    return m_is_mandatory;
}

template< typename T >
std::string
program_option_with_value< T >::name() const
{
    return m_name ;
}

template< typename T>
char
program_option_with_value< T >::short_name() const
{
    return m_short_name ;
}

template< typename T >
std::string
program_option_with_value< T >::description() const
{
    return m_description ;
}

template< typename T >
std::string
program_option_with_value< T >::short_description() const
{
    return "--" + m_name + "=" + breath::readable_type_name< T >() ;
}

template< typename T >
std::string
program_option_with_value< T >::full_description( std::string const & descr )
{
    return
        descr + " (" + breath::readable_type_name< T >() +
            ( m_is_mandatory
                ? ""
                : " [=" + breath::to_string( m_default_value ) + "]"
            )
        + ")" ;
}

template< typename T >
T
program_option_with_value< T >:: read( std::string const & s )
{
    return m_reader( s ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
