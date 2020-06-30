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

#include "breath/stream/null_stream.hpp"
#include "breath/iteration/begin_end.hpp"

namespace breath_ns {

null_stream_buffer::null_stream_buffer()
{
    set_put_area_pointers() ;
}

null_stream_buffer::int_type
null_stream_buffer::overflow( int_type c )
{
    set_put_area_pointers() ;

    //      Would it be worthwhile to use not_eof( c )?
    // -----------------------------------------------------------------------
    return traits_type::eq_int_type( c, traits_type::eof() )
                ? char_type()
                : c
                ;
}

null_stream_buffer::int_type
null_stream_buffer::underflow()
{
    return traits_type::eof() ;
}

void
null_stream_buffer::set_put_area_pointers()
{
    setp( breath::begin( m_dummy_buffer ),
          breath::end(   m_dummy_buffer ) ) ;
}

null_stream::null_stream()
    :   std::istream( buffer_wrapper_type::stream_buffer() ),
        std::ostream( buffer_wrapper_type::stream_buffer() )
{
}

null_stream_buffer *
null_stream::rdbuf() const
{
    auto * const p = const_cast< null_stream * >( this ) ;
    return p->stream_buffer() ;
}

}

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
