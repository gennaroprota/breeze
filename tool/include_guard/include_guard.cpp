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
//
//      Generates an include guard (for a new source file or for an
//      existing one---but see below).
//
//      Synopsis:
//      ---------
//
//          include_guard [-p macro_prefix]
//
//      Limitations:
//      ------------
//
//      To use an existing file as input, or to generate a new source
//      file, it is intended that you employ redirection or a pipe: the
//      tool always reads from the standard input; and outputs what it
//      reads (if anything) to the standard output, enclosed in the
//      classical #ifndef/#endif.
//
//      It cannot be properly interrupted by a signal: in particular, if
//      this happens while reading from standard input it will usually
//      just skip further reading, as if EOF was encountered.
//
//      Options:
//      --------
//
//        -p or --prefix
//
//          The prefix to use for the generated macro name. Default =
//          BREEZE_.
//
//          Prefixes which would make the macro name reserved are
//          rejected.
//
//      Example:
//      --------
//
//      Assuming the executable is called "include_guard" and is
//      invoked with
//
//        include_guard --prefix MY_PREFIX_
//
//      a possible output is:
//
//                                       random part
//                          |------------------------------|
//        #ifndef MY_PREFIX_XcocANDF5GeFUffA3GTta5eUcluqZwhM
//        #define MY_PREFIX_XcocANDF5GeFUffA3GTta5eUcluqZwhM
//        <newline1><contents from standard input...><newline2>
//        #endif
//
//      Note:
//          newline2 is omitted if no characters are available from
//          standard input.
// ---------------------------------------------------------------------------

#include "tool/include_guard/macro_name.hpp"
#include "breeze/process/command_line.hpp"
#include "breeze/process/program.hpp"
#include "breeze/process/program_option.hpp"

#include <cstdio> // for EOF
#include <exception>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

namespace {

breeze::default_reader< std::string >
                    option_reader ;
breeze::program_option_with_value< std::string >
                    prefix_option( "prefix", 'p', false, "BREEZE_GUARD_", "macro prefix", option_reader ) ;

}

int
main( int argc, char ** argv )
{
    using               breeze::command_line ;
    using               breeze::program ;

    try {
        command_line::instance().parse_check( argc, argv ) ;
        std::string const   prefix = prefix_option.get() ;

        if ( ::is_reserved( prefix ) ) {
            std::cerr << "Can't use a reserved name; please, change your prefix"
                         " (see [lex.name] in the C++ standard)" ;
            program::instance().declare_error( program::fatal ) ;
        }

        int const           random_part_length = 32 ;

        macro_name_creation::exit_status
                            status ;
        std::string const   name =
            ::make_macro_name( prefix, random_part_length, &status ) ;

        if ( status == macro_name_creation::could_not_release_entropy_source ) {
            std::cerr << "Unable to release the entropy source" << std::endl ;
            program::instance().declare_error( program::comment ) ;
        }

        std::cout << "#ifndef " << name   << std::endl
                  << "#define " << name   << std::endl ;

        std::cout                         << std::endl ;
        if ( std::cin.peek() != EOF ) {
            std::cout << std::cin.rdbuf() << std::endl ;
        }
        std::cout << "#endif"             << std::endl ;

    } catch ( std::exception const & ex ) {
        std::cerr << ex.what() << std::endl ;
        program::instance().declare_error( program::error ) ;
    } catch ( ... ) {
        std::cerr << "An unknown exception occurred" << std::endl ;
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
