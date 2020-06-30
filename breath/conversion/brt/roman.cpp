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

#include "breath/conversion/roman.hpp"
#include "breath/diagnostics/assert.hpp"
#include <ostream>

namespace breath_ns {

roman::roman( int n )
    :   m_value( n )
{
    BREATH_ASSERT( 1 <= n && n <= 3999 ) ;
}

std::ostream &
operator <<( std::ostream & os, roman const & r )
{
    static struct entry
    {
        int                 value ;
        char const *        upper_repr ;
        char const *        lower_repr ;
    } const             table[] = {
{ 1000, "M",  "m"  },
 { 900, "CM", "cm" }, { 500, "D", "d" }, { 400, "CD", "cd" }, { 100, "C", "c" },
  { 90, "XC", "xc" },  { 50, "L", "l" },  { 40, "XL", "xl" },  { 10, "X", "x" },
   { 9, "IX", "ix" },   { 5, "V", "v" },   { 4, "IV", "iv" },   { 1, "I", "i" }
    } ;

    char const * entry::* const
                        repr = ( os.flags() & std::ios_base::uppercase ) != 0
                                   ? &entry::upper_repr
                                   : &entry::lower_repr ;

    std::string         output ;
    entry const *       p = &table[ 0 ] ;
    int                 n = r.m_value ;
    do {
        for ( int i = 0 ; i < n / p->value ; ++ i ) {
            output += p->*repr ;
        }
        n %= p->value ;
        ++ p ;
    } while ( n != 0 ) ;

    return os << output ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
