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
//        include_guard [options]
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
//        -p or --prefix=WORD
//
//          The prefix to use for the generated macro name. Default =
//          BREEZE_GUARD_.
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
#include "breeze/process/program.hpp"
#include "breeze/text/begins_with.hpp"

#include <cstdio> // for EOF
#include <exception>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

namespace {

std::string         macro_prefix = "BREEZE_GUARD_" ;

std::string         remove_from_beginning( std::string const & s,
                                           std::string const & to_be_removed )
{
    return breeze::begins_with( s, to_be_removed )
        ? s.substr( to_be_removed.length() )
        : s
        ;
}

//      parse_command_line():
//      =====================
//
//      A rudimentary, ad-hoc, command line parser which we'll use until
//      we'll have a corresponding general facility in the library.
// ---------------------------------------------------------------------------
bool
parse_command_line( int argc, char const * const * argv )
{
    bool                result = false ;
    if ( argc == 1 ) {
        result = true ;
    } else if ( argc == 2 ) {
        std::string         arg = argv[ 1 ] ;
        std::string const   long_option  = "--prefix" ;
        std::string const   short_option = "-p" ;
        bool                option_found = false ;
        if ( breeze::begins_with( arg, long_option ) ) {
            arg = remove_from_beginning( arg, long_option ) ;
            arg = remove_from_beginning( arg, "=" ) ;
            option_found = true ;
        } else if ( breeze::begins_with( arg, short_option ) ) {
            arg = remove_from_beginning( arg, short_option ) ;
            option_found = true ;
        }

        if ( option_found ) {
            macro_prefix = arg ;
            result = ! arg.empty() ;
        }
    }

    return result ;
}

}

int
main( int argc, char ** argv )
{
    using               breeze::program ;

    try {
        if ( ! parse_command_line( argc, argv ) ) {
            program::instance().declare_error( program::fatal,
                "Erroneous invocation; see usage in include_guard.cpp") ;
        }

        if ( ::is_reserved( macro_prefix ) ) {
            program::instance().declare_error( program::fatal,
                "Can't use a reserved name; please, change your prefix"
                " (see [lex.name] in the C++ standard)" ) ;
        }

        int const           random_part_length = 32 ;

        macro_name_creation::exit_status
                            status ;
        std::string const   name =
            ::make_macro_name( macro_prefix, random_part_length, &status ) ;

        if ( status == macro_name_creation::could_not_release_entropy_source ) {
            program::instance().declare_error( program::comment,
                "Unable to release the entropy source" ) ;
        }

        std::cout << "#ifndef " << name   << std::endl
                  << "#define " << name   << std::endl ;

        std::cout                         << std::endl ;
        if ( std::cin.peek() != EOF ) {
            std::cout << std::cin.rdbuf() << std::endl ;
        }
        std::cout << "#endif"             << std::endl ;

    } catch ( std::exception const & ex ) {
        program::instance().declare_error( program::error, ex.what() ) ;
    } catch ( ... ) {
        program::instance().declare_error( program::fatal,
            "An unknown exception occurred" ) ;
    }
    return program::instance().exit_code() ;
}
