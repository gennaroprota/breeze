// ===========================================================================
//                        Copyright 2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________

#include "breath/iteration/begin_end.hpp"

namespace breath {

template< typename Ch, typename Traits >
basic_null_stream_buffer< Ch, Traits >::basic_null_stream_buffer()
{
    set_put_area_pointers() ;
}

template< typename Ch, typename Traits >
typename basic_null_stream_buffer< Ch, Traits >::int_type
basic_null_stream_buffer< Ch, Traits >::overflow( int_type c )
{
    set_put_area_pointers() ;
    return Traits::eq_int_type( c, Traits::eof() )
                ? Ch()
                : c
                ;
}

template< typename Ch, typename Traits >
typename basic_null_stream_buffer< Ch, Traits >::int_type
basic_null_stream_buffer< Ch, Traits >::underflow()
{
    return Traits::eof() ;
}

template< typename Ch, typename Traits >
void
basic_null_stream_buffer< Ch, Traits >::set_put_area_pointers()
{
    this->setp( breath::begin( m_dummy_buffer ),
                breath::end(   m_dummy_buffer ) ) ;
}

template< typename Ch, typename Traits >
basic_null_stream< Ch, Traits >::basic_null_stream()
    :   std::basic_ostream< Ch, Traits >( this ),
        std::basic_istream< Ch, Traits >( this )
{
}

template< typename Ch, typename Traits >
basic_null_stream_buffer< Ch, Traits > *
basic_null_stream< Ch, Traits >::rdbuf() const
{
    basic_null_stream_buffer< Ch, Traits > const *
                        p = this ;
    return const_cast< basic_null_stream_buffer< Ch, Traits > * >( p ) ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
