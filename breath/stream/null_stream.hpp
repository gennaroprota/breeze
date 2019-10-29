// ===========================================================================
//                        Copyright 2017 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief A stream that discards any output to it and never has
//!            characters in input.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_CnvhAthmCrzPoNDMrZPUfBrAGrgy3Xe0
#define BREATH_GUARD_CnvhAthmCrzPoNDMrZPUfBrAGrgy3Xe0

#include <istream>
#include <ostream>
#include <streambuf>

namespace breath {

//! \cond
template< typename Ch, typename Traits = std::char_traits< Ch > >
class basic_null_stream_buffer
    :   public std::basic_streambuf< Ch, Traits >
{
public:
    typedef std::basic_streambuf< Ch, Traits >
                        base_type ;
    typedef typename base_type::int_type
                        int_type ;

                        basic_null_stream_buffer() ;

protected:
    virtual int_type    overflow( int_type c ) override ;
    virtual int_type    underflow() override ;

private:
    void                set_buffer() ;

    //  Having a buffer avoids some virtual function calls.
    // -----------------------------------------------------------------------
    Ch                  m_dummy_buffer[ 64 ] ;
} ;
//! \endcond

//!     basic_null_stream:
//!     ------------------
//!
//!     An iostream that discards any output and provides no input. On
//!     output, the stream never signals failbit. On input it is
//!     always on EOF. The behavior is similar to a file stream
//!     opened on /dev/null under Unix, but this is portable and
//!     doesn't make system calls.
// ---------------------------------------------------------------------------
template< typename Ch, typename Traits = std::char_traits< Ch > >
class basic_null_stream
    :   private basic_null_stream_buffer< Ch, Traits >,
        public  std::basic_ostream< Ch, Traits >,
        public  std::basic_istream< Ch, Traits >
{
public:
                        basic_null_stream() ;
    virtual             ~basic_null_stream() noexcept override = default ;

    basic_null_stream_buffer< Ch, Traits > *
                        rdbuf() const ;
} ;

typedef basic_null_stream< char >
                    null_stream ;
typedef basic_null_stream< wchar_t >
                    wide_null_stream ;

}

#include "brt/null_stream.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
