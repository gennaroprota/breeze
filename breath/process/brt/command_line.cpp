// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2017 Gennaro Prota
//                       Copyright 2009 Hideyuki Tanaka
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/process/command_line.hpp"
#include "breath/counting/signed_count.hpp"
#include "breath/preprocessing/prevent_macro_expansion.hpp"
#include "breath/process/program.hpp"
#include "breath/process/program_option.hpp"
#include "breath/text/begins_with.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>

namespace breath {

command_line *
command_line::s_instance = &command_line::instance() ;

void
command_line::add( program_option_without_value & opt )
{
    std::string const   name = opt.name() ;
    if ( m_options.count( name ) != 0 ) {
        throw command_line_error( "multiple definition: " + name ) ;
    }

    m_options[ name ] = &opt ;
    m_ordered.push_back( m_options[ name ] ) ;
}

command_line &
command_line::instance()
{
    if ( s_instance == nullptr ) {
        s_instance = new command_line ;
    }

    return *s_instance ;
}

//      TODO: This function is too long.
// ---------------------------------------------------------------------------
bool
command_line::parse( int argc,  char const * const * argv )
{
    m_errors.clear() ;
    m_rest.clear() ;

    if ( argc < 1 ) {
        m_errors.push_back( "argc must be greater than 0" ) ;
        return false ;
    }

    program::instance().set_name( argc, argv ) ;

    std::map< char, std::string > lookup ;
    for (std::map< std::string, option_base * >::const_iterator it = 
                                                m_options.cbegin() ;
                                                it != m_options.cend() ; ++ it ) {
        if ( it->first.length() == 0 ) {
            continue ;
        }
        char const          initial = it->second->short_name() ;
        if ( initial != '\0' ) {
            if ( lookup.count( initial ) > 0 ) {
                lookup[ initial ]= "" ;
                m_errors.push_back( std::string( "short option '" ) + initial +
                                                               "' is ambiguous" ) ;
                return false ;
            }
            else {
                lookup[ initial ] = it->first ;
            }
        }
    }

    for ( int i = 1 ; i < argc ; ++ i ) {
        char const          dashdash[] = "--" ;
        if ( begins_with( argv[i], dashdash ) ) {
            char const * const  p = std::strchr( argv[ i ] +
                                            ( breath::signed_count( dashdash ) - 1 ), '=' ) ;
            if ( p != nullptr ) {
                std::string const   name( argv[ i ] + ( breath::signed_count(dashdash) - 1 ), p ) ;
                std::string const   value( p + 1 ) ;
                set_option( name, value ) ;
            } else {
                std::string name( argv[ i ] + ( breath::signed_count( dashdash ) - 1 ) ) ;
                if ( m_options.count( name ) == 0 ) {
                    m_errors.push_back( "undefined option: --" + name ) ;
                    continue ;
                }
                if ( m_options[name]->has_value() ) {
                    if ( i + 1 >= argc ) {
                        m_errors.push_back( "option needs value: --" + name ) ;
                        continue ;
                    } else {
                        ++ i ;
                        set_option( name, argv[ i ] ) ;
                    }
                } else {
                    set_option(name) ;
                }
            }
        }
        else if ( begins_with( argv[ i ], "-" ) ) {
            char            last = argv[ i ][ 1 ] ;
            if ( last == '\0' ) {
                continue ;
            }
            
            for ( int j = 2 ; argv[ i ][ j ] != '\0' ; ++ j ) {
                last = argv[ i ][ j ] ;
                if ( lookup.count( argv[ i ][ j - 1 ] ) == 0 ) {
                    m_errors.push_back( std::string( "undefined short option: -" ) + argv[ i ] [j - 1 ] ) ;
                    continue ;
                }
                if ( lookup[ argv[ i ][ j - 1 ] ] == "" ) {
                    m_errors.push_back( std::string( "ambiguous short option: -" ) + argv[ i ][ j - 1 ] ) ;
                    continue ;
                }
                set_option( lookup[argv[ i ][ j - 1 ] ] ) ;
            }

            if ( lookup.count( last ) == 0 ) {
                m_errors.push_back( std::string( "undefined short option: -" ) + last ) ;
                continue ;
            }
            if ( lookup[ last ] == "" ) {
                m_errors.push_back( std::string( "ambiguous short option: -" ) + last ) ;
                continue ;
            }

            if ( i + 1 < argc && m_options[ lookup[ last ] ]->has_value() ) {
                set_option( lookup[ last ], argv[ i + 1 ] ) ;
                ++ i ;
            } else {
                set_option( lookup[ last ] ) ;
            }
        } else {
            m_rest.push_back( argv[ i ] ) ;
        }
    }

    for ( auto it = m_options.cbegin() ; it != m_options.cend() ; ++ it ) {
        if ( ! it->second->is_valid() ) {
            m_errors.push_back( "need option: --" + std::string( it->first ) ) ;
        }
    }
    return m_errors.empty() ;
}

void
command_line::parse_check( int argc, char const * const * argv )
{
    if ( ! m_options.count( "help" ) ) {
        add( help_option ) ;
    }
    check( argc, parse( argc, argv ) ) ;
}

void
command_line::check( int argc, bool ok )
{
    if ( ( argc == 1 && ! ok ) || help_option.is_set() /*exists( "help" )*/ )
    {
        std::cerr << usage() ;
        std::exit( program::instance().exit_code() ) ;
    }

    if ( ! ok ) {
        program::instance().declare_error( program::error ) ;
        std::cerr << error() << std::endl << usage() ;
        std::exit( program::instance().exit_code() ) ;
    }
}

std::string
command_line::usage() const
{
    std::ostringstream  oss ;
    oss << "Usage: " << program::instance().name().default_to( "program-name" )
        << ' ' ;
    for ( auto const & ord: m_ordered ) {
        if ( ord->is_mandatory() ) {
            oss << ord->short_description() << " " ;
        }
    }
    
    oss << "[options] ... " << std::endl ;
    oss << "options:" << std::endl ;

    std::size_t         max_width = 0 ;
    for ( std::size_t i = 0 ; i < m_ordered.size() ; ++ i ) {
        max_width = std::max BREATH_PREVENT_MACRO_EXPANSION
                    ( max_width, m_ordered[ i ]->name().length() ) ;
    }
    for (std::size_t i = 0 ; i < m_ordered.size() ; ++ i ) {
        if ( m_ordered[ i ]->short_name() != '\0' ){
            oss << "  -" << m_ordered[ i ]->short_name( ) << ", " ;
        } else {
            oss << "      " ;
        }

        oss << "--" << m_ordered[ i ]->name() ;
        int const       additional = 4 ;
        std::string const
                        spaces( max_width + additional -
                                m_ordered[ i ]->name().length(), ' ' ) ;

        oss << spaces ;
        oss<< m_ordered[ i ]->description() << std::endl ;
    }
    return oss.str() ;
}

std::string
command_line::error() const
{
    return m_errors.empty()
        ? ""
        : m_errors[ 0 ]
        ;
}

void
command_line::set_option( std::string const & name )
{
    if ( m_options.count( name ) == 0 ) {
        m_errors.push_back( "undefined option: --" + name ) ;
        return ;
    }
    if ( ! m_options[ name ]->set() ) {
        m_errors.push_back( "option needs value: --" + name ) ;
        return ;
    }
}

void
command_line::set_option( std::string const & name, const std::string & value )
{
    if ( m_options.count( name ) == 0 ) {
        m_errors.push_back( "undefined option: --" + name ) ;
        return ;
    }
    if ( ! m_options[ name ]->set( value ) ) {
        m_errors.push_back( "option value is invalid: --" + name + "=" + value ) ;
        return ;
    }
}

#if 0
bool
command_line::exists( const std::string & name ) const
{
    if ( m_options.count( name ) == 0 ) {
        throw command_line_error( "missing option: --" + name ) ;
    }
    return m_options.find( name )->second->is_set() ;
}
#endif

std::vector< std::string >
command_line::rest() const
{
    return m_rest ;
}

command_line_error::command_line_error( std::string const & msg )
    : exception( msg )
{
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
