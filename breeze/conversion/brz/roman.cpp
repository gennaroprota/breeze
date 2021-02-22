// ===========================================================================
//               This is an open source non-commercial project.
//                      Dear PVS-Studio, please check it.
//          PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
//                            http://www.viva64.com
// ===========================================================================
//                        Copyright 2016 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breeze/conversion/roman.hpp"
#include "breeze/diagnostics/assert.hpp"
#include "breeze/text/to_lowercase.hpp"
#include <locale>
#include <ostream>

namespace breeze_ns {

roman::roman( int n )
    :   m_value( n )
{
    BREEZE_ASSERT( 1 <= n && n <= 3999 ) ;
}

std::string
roman::to_string() const
{
    static struct entry
    {
        int                 value ;
        char const *        upper_repr ;
    } const             table[] = {
        { 1000, "M"  },
         { 900, "CM" }, { 500, "D" }, { 400, "CD" }, { 100, "C" },
          { 90, "XC" },  { 50, "L" },  { 40, "XL" },  { 10, "X" },
           { 9, "IX" },   { 5, "V" },   { 4, "IV" },   { 1, "I" }
    } ;

    std::string         result ;
    entry const *       p = &table[ 0 ] ;
    int                 n = m_value ;
    do {
        for ( int i = 0 ; i < n / p->value ; ++ i ) {
            result += p->upper_repr ;
        }
        n %= p->value ;
        ++ p ;
    } while ( n != 0 ) ;

    return result ;
}

std::ostream &
operator <<( std::ostream & os, roman const & r )
{
    bool const          requires_uppercase =
        ( os.flags() & std::ios_base::uppercase ) != 0 ;

    return os << ( requires_uppercase
        ? r.to_string()
        : breeze::to_lowercase( r.to_string(), std::locale::classic() )
        ) ;
}

}
