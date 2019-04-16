// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                     Copyright 2008-2015 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "tool/include_guard/macro_name.hpp"
#include "breath/diagnostics/exception.hpp"
#include "breath/process/command_line.hpp"
#include "breath/process/program.hpp"
#include "breath/process/program_option.hpp"

#include <cstdio> // for EOF
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

namespace {

breath::default_reader< std::string >
                    option_reader ;
breath::program_option_with_value< std::string >
                    prefix_option( "prefix", 'p', false, "BREATH_GUARD_", "macro prefix", option_reader ) ;

}

int
main( int argc, char ** argv )
{
    using               breath::command_line ;
    using               breath::program ;

    try {
        command_line::instance().parse_check( argc, argv ) ;
        std::string const   prefix = prefix_option.get() ;
        int const           random_part_length = 32 ;

        macro_name_creation::exit_status
                            status ;
        std::string const   name =
            ::make_macro_name( prefix, random_part_length, &status ) ;

        if ( status == macro_name_creation::could_not_release_entropy_source ) {
            std::cerr << "Unable to release the entropy source." << std::endl ;
            program::instance().declare_error( program::comment ) ;
        }

        std::cout << "#ifndef " << name   << std::endl
                  << "#define " << name   << std::endl    ;
        if ( std::cin.peek() != EOF ){
            std::cout << std::cin.rdbuf() << std::endl    ;
        }
        std::cout << "#endif"             << std::endl    ;

    } catch (std::exception const & ex ) {
        std::cerr << ex.what() << std::endl ;
        program::instance().declare_error( program::error ) ;
    } catch ( ... ) {
        program::instance().declare_error( program::fatal ) ;
    }
    return program::instance().exit_code() ;
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
