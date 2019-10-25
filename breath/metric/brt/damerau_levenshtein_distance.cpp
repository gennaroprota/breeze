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

#include "breath/metric/damerau_levenshtein_distance.hpp"
#include "breath/idiom/declare_non_copyable.hpp"
#include <algorithm>
#include <cstddef>

namespace breath {
namespace        {

class matrix
{
public:
    BREATH_DECLARE_NON_COPYABLE( matrix )

    typedef std::ptrdiff_t T ;
                        matrix( std::ptrdiff_t rows, std::ptrdiff_t columns )
                            :   m_columns( columns ),
                                m_data( new T[ rows * columns ] )
                        {
                        }

    T *                operator[]( std::ptrdiff_t i ) noexcept
    {
        return m_data + i * m_columns ;
    }

                        ~matrix() noexcept
                        {
                            delete[] m_data ;
                        }
private:
    std::ptrdiff_t      m_columns ;
    T * const           m_data ;
} ;

}

//      I could not find any algorithm with a space complexity below
//      O( n^2 ). If you know of one, please drop me a mail.
// ---------------------------------------------------------------------------
std::ptrdiff_t
damerau_levenshtein_distance( std::string const & first,
                              std::string const & second )
{
    typedef std::ptrdiff_t
                        length_type ;

    length_type const   height = 1 + first.length() ;
    length_type const   width  = 1 + second.length() ;

    matrix              m( height, width ) ;
    for ( length_type i = 0 ; i < height ; ++ i ) {
        m[ i ][ 0 ] = i ;
    }
    for ( length_type j = 0 ; j < width ; ++ j ) {
        m[ 0 ][ j ] = j ;
    }
    for ( length_type i = 1 ; i < height ; ++ i ) {
        for ( length_type j = 1 ; j < width ; ++ j ) {
            int const           cost = first[ i - 1 ] == second[ j - 1 ]
                                            ? 0
                                            : 1
                                            ;
            length_type const   insertion    = m[ i ][ j - 1 ] + 1 ;
            length_type const   deletion     = m[ i - 1 ][ j ] + 1 ;
            length_type const   substitution = m[ i - 1 ][ j - 1 ] + cost ;
            length_type         distance     = (std::min)( { insertion,
                                                             deletion,
                                                             substitution } ) ;
            if ( i > 1 && j > 1  && first[ i - 1 ] == second[ j - 2 ] &&
                first[ i - 2 ] == second[ j - 1 ] ) {
                distance = (std::min)( distance, m[ i - 2 ][ j - 2 ] + cost ) ;
            }
            m[ i ][ j ] = distance ;
        }
    }
    return m[ height - 1 ][ width - 1 ] ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
