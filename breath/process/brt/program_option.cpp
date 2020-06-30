// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/process/program_option.hpp"
#include "breath/process/command_line.hpp"

namespace breath_ns {

program_option_without_value
                    help_option( "help", '?', "prints this message" ) ;

program_option_without_value::program_option_without_value(
                            std::string const & name,
                            char short_name,
                            std::string const & description )
      : m_name( name ), m_short_name( short_name ), m_description( description ),
        m_is_set( false )
{
    command_line::instance().add( *this ) ;
}

bool
program_option_without_value::has_value() const
{
    return false ;
}

bool
program_option_without_value::set()
{
    m_is_set = true ;
    return true ;
}

bool
program_option_without_value::set( std::string const & )
{
    return false ;
}

bool
program_option_without_value::is_set() const
{
    return m_is_set ;
}

bool
program_option_without_value::is_valid() const
{
    return true ;
}

bool
program_option_without_value::is_mandatory() const
{
    return false ;
}

std::string
program_option_without_value::name() const
{
    return m_name ;
}

char
program_option_without_value::short_name() const
{
    return m_short_name ;
}

std::string
program_option_without_value::description() const
{
    return m_description ;
}

std::string
program_option_without_value::short_description() const
{
    return "--" + m_name ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
