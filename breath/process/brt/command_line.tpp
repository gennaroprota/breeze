// ===========================================================================
//                        Copyright 2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

namespace breath_ns {

template< typename T >
void
command_line::add( program_option_with_value< T > & opt )
{
    std::string const   name = opt.name() ;
    if ( m_options.count( name ) != 0 ) {
        throw command_line_error( "multiple program option definition: \'" + name + "\'" ) ;
    }
    m_options[ name ] = &opt ;
    m_ordered.push_back( &opt ) ;
}

#if 0
template< typename T >
program_option_with_value< T > const &
command_line::get( std::string const & name ) const
{
    if ( m_options.count( name ) == 0 ) {
        throw command_line_error( "there is no flag: --" + name ) ;
    }
    program_option_with_value< T > const *
                        p= dynamic_cast< program_option_with_value< T > const *
                                       >( m_options.find( name )->second ) ;
    if ( p == nullptr ) { 
        throw command_line_error( "type mismatch flag '" + name + "'" ) ;
    }
    return *p ;
}
#endif

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
