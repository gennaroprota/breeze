// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2013 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//      line_up:
//      ========
//
//      Aligns the backslashes in a multi-line macro definition. Works
//      like a Unix filter. Terminates the last line with "/**/".
//
//      If the backslashes are not present in the input, it inserts
//      them. Tab characters are always expanded.
//
//      Note that the tool aborts if there are less than two lines in
//      the input.
// ---------------------------------------------------------------------------

#include "breath/diagnostics/assert.hpp"
#include "breath/text/remove_from_end.hpp"
#include "breath/text/trim_tail.hpp"

#include <algorithm>
#include <cstdio> // for EOF
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <vector>

namespace {

//      Configuration constants (will be command line arguments):
//      =========================================================
//
//      Put the normal_line_terminator at column 1 + k * indent_width,
//      with k being a positive integer (at least one space is added).
// ---------------------------------------------------------------------------
bool const          use_indent_width = true ;

int const           indent_width = 4 ;

//      This is made a string for generality, but we really only need a
//      character for now.
// ---------------------------------------------------------------------------
std::string const   normal_line_terminator( "\\" ) ;

std::string const   last_line_terminator( "/**/" ) ;


//      read_all():
//      ===========
//
//      Reads all lines from 'in', stripping all normal_line_terminators
//      and spaces that (immediately) precede or follow them. Newlines
//      are stripped, too. Tab characters are expanded.
// ---------------------------------------------------------------------------
std::vector< std::string >
read_all( std::istream & in )
{
    std::vector< std::string >
                        result ;
    std::string         line ;

    while ( in.peek() != EOF ) {
        char const          ch = static_cast< char >( in.get() ) ;

        switch ( ch ) {

        case '\n':
            line = breath::trim_tail( line ) ;
            line = breath::remove_from_end( line, normal_line_terminator ) ;
            line = breath::trim_tail( line ) ;

            result.push_back( line ) ;
            line.clear() ;
            break ;

        case '\t':
            line += std::string( indent_width - line.length() % indent_width,
                                 ' ' ) ;
            break ;

        default:
            line += ch ;
            break ;
        }
    }

    return result ;
}

//      max_element_length():
//      =====================
//
//      Returns 0 if 'v' is empty; otherwise the length of the longest
//      string in 'v'.
// ---------------------------------------------------------------------------
std::string::size_type
max_element_length( std::vector< std::string > const & v )
{
    auto const          iter =
            std::max_element( v.cbegin(), v.cend(),
                              []( std::string const & a, std::string const & b )
                              {
                                  return a.length() < b.length() ;
                              } ) ;

    return iter == v.cend()
               ? 0
               : iter->length() ;
}

}

int
main()
{
    typedef std::string::size_type
                        size_type ;

    std::istream &      in( std::cin ) ;
    std::vector< std::string> const
                        lines( read_all( in ) ) ;

    BREATH_ASSERT( lines.size() > 1 ) ;

    size_type const     max_length = max_element_length( lines ) ;

    size_type column =
        last_line_terminator.length() > normal_line_terminator.length()
            ? max_length + 2 + ( last_line_terminator.length() -
                                 normal_line_terminator.length() )
            : max_length + 2 ;

    if ( use_indent_width && ( column % indent_width ) != 1 ) {
        if ( ( column % indent_width ) == 0 ) {
            column += 1 ;
        } else {
            column += ( indent_width - column % indent_width + 1 ) ;
        }
    }

    for ( auto it = lines.cbegin() ; it != lines.cend() ; ++ it ) {

        bool const          is_last_line = it == lines.cend() - 1 ;

        size_type const     space_count = is_last_line
                                ? column - 1 - it->length()             -
                                        last_line_terminator.length()   +
                                        normal_line_terminator.length()
                                : column - 1 - it->length() ;

        std::string const   spaces( space_count, ' ' ) ;

        std::cout << *it << spaces << ( is_last_line
                                          ? last_line_terminator
                                          : normal_line_terminator )
                                                                  << std::endl ;

    }
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
