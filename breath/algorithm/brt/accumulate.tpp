// ===========================================================================
//                     Copyright 2006-2010 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

namespace breath {

template< typename T >
typename accumulate_traits< T >::init_type
accumulate_traits< T >::first()
{
   return T() ;
}

template< typename T >
template< typename Iter >
typename accumulate_traits< T >::result_type
accumulate_traits< T >::compute( Iter begin,
                                 Iter end,
                                 init_type & value )
{
    while ( begin != end ) {
        value += *begin ;
        ++ begin ;
    }
    return value ;
}

template< typename InputIterator, typename T >
typename accumulate_traits< T >::result_type
accumulate( InputIterator begin,
            InputIterator end,
            T v )
{
    return breath::accumulate_traits< T >::compute( begin, end, v ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
