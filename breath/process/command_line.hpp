// =========================================================================
//                       Copyright 2017 Gennaro Prota
//                      Copyright 2009 Hideyuki Tanaka
//
//                 Licensed under the 3-Clause BSD License.
//            (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//             <https://opensource.org/licenses/BSD-3-Clause>.)
// _________________________________________________________________________

#ifndef BREATH_GUARD_wv85pwyBmJzlhg6z02PPsgOP4CY3kdBn
#define BREATH_GUARD_wv85pwyBmJzlhg6z02PPsgOP4CY3kdBn

#include "breath/diagnostics/exception.hpp"
#include "breath/idiom/declare_non_copyable.hpp"

#include <map>
#include <string>
#include <vector>

namespace breath {

class               program_option_without_value ;

template< typename T >
class               program_option_with_value ;

class               option_base ;

class command_line
{
public:
    BREATH_DECLARE_NON_COPYABLE( command_line )

private:
                        command_line() = default ;

    void                add( program_option_without_value & opt ) ;
    template< typename T >
    void                add( program_option_with_value< T > & opt ) ;

    friend              program_option_without_value ;
    template< typename T >
    friend class        program_option_with_value;

public:
    //!     The library arranges for calling this before main starts().
    // ---------------------------------------------------------------------
    static command_line &
                        instance() ;

//   void                 parse_check( const std::string & arg ) ;
    bool                parse( int argc,  char const * const * argv ) ;
    void                parse_check( int argc, char const * const * argv ) ;

//    bool                exists( std::string const & name ) const ;
    std::vector<std::string>
                        rest() const ;
    std::string         usage() const ;
    std::string         error() const ;

#if 0
    template< typename T > program_option_with_value< T > const &
                        get( std::string const & name ) const ;
#endif

private:
    void                set_option( std::string const & name ) ;
    void                set_option( std::string const & name, std::string const & value ) ;
    void                check( int argc, bool ok ) ;

    std::map<std::string, option_base * >
                        m_options ;
    std::vector< option_base * >
                        m_ordered ;
    std::vector< std::string >
                        m_rest ;
    std::vector< std::string >
                        m_errors;

    static command_line *
                        s_instance ;
} ;

class command_line_error
    :   public virtual breath::exception
{
public:
    explicit            command_line_error( std::string const & msg ) ;
};

}

#include "brt/command_line.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
