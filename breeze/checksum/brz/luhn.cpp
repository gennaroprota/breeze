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

#include "breeze/checksum/luhn.hpp"
#include "breeze/counting/signed_count.hpp"
#include <numeric>
#include <stdexcept>

namespace breeze_ns {
namespace           {

int const           table[] = { 0, 2, 4, 6, 8, 1, 3, 5, 7, 9 } ;
int const           base = static_cast< int >( breeze::signed_count( table ) ) ;

//      Use this in lieu of std::isdigit(), because, under Microsoft
//      with codepage 1252, std::isdigit() also returns true for some
//      superscript digits (which is non-conforming).
// ---------------------------------------------------------------------------
bool
portable_is_digit( char c )
{
    return '0' <= c && c <= '9' ;
}

}

int
luhn_sum( std::string const & s )
{
    bool                from_table = false ;
    auto checked_adder = [ &from_table ]( int old_sum, char c )
    {
        if ( ! portable_is_digit( c ) ) {
            throw std::invalid_argument( "non-digit char in Luhn string" ) ;
        }
        int const           value = c - '0' ;
        int const           sum = old_sum + ( from_table
                                                ? table[ value ]
                                                : value ) ;
        from_table = ! from_table ;
        return sum % base ;
    } ;

    return std::accumulate( s.crbegin(), s.crend(), 0, checked_adder ) ;
}

bool
has_luhn_sum( std::string const & s )
{
    return ! s.empty() && luhn_sum( s ) == 0 ;
}

char
luhn_check_digit( std::string const & s )
{
    int const           sum = luhn_sum( s + '0' ) ;
    return static_cast< char >( '0' + ( ( base - sum ) % base ) ) ;
}

}
