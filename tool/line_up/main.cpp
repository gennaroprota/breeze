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

//      Configuration constants (will be command line arguments).
// ---------------------------------------------------------------------------
bool const          use_indent_width = true ; // put the marker at 1 + k*w, where w
                                              // is the indentation width (at least
                                              // one space is added)
int const           indent_width = 4 ;
bool const          expand_tabs = true ;

// This is made a string for generality, but we really only need a
// character for now.
std::string const   marker( "\\" ) ;

std::string const   last_line_terminator( "/**/" ) ;

}

int
main()
{
    std::istream &      in( std::cin ) ;
    std::string         line ;
    std::vector< std::string >
                        lines ;
    typedef std::string::size_type
                        size_type ;
    size_type           max_length = 0 ;

    while ( in.peek() != EOF ) {

        char const          ch = static_cast< char >( in.get() ) ;
        if ( ch == '\n' ) {

            // remove <spaces><marker><spaces>
            //
            line = breath::trim_tail( line ) ;
            line = breath::remove_from_end( line, marker ) ;
            line = breath::trim_tail( line ) ;

            lines.push_back( line ) ;

            if ( line.length() > max_length ) {
                max_length = line.length() ;
            }
            line.clear() ;
        } else if ( ch== '\t' && expand_tabs ) {
                line += std::string( indent_width, ' ' ) ;
        } else {
            line += ch ;
        }
    }

    max_length += std::max( last_line_terminator.length(),
                            marker.length() ) ;
    for ( auto it = lines.begin() ; it != lines.end() ; ++ it ) {

        // gps perhaps do a calculation here
        do {
            *it += ' ' ;
        } while ( it->length() <= max_length
            || ( use_indent_width && ( it->length() % indent_width != 0 ) ) ) ;


        std::cout << *it << ( it == ( lines.end() - 1 )
                                ? last_line_terminator
                                : marker ) << std::endl ;

    }
}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
