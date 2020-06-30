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
//!            characters in input, plus its corresponding stream
//!            buffer.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_CnvhAthmCrzPoNDMrZPUfBrAGrgy3Xe0
#define BREATH_GUARD_CnvhAthmCrzPoNDMrZPUfBrAGrgy3Xe0

#include "breath/top_level_namespace.hpp"
#include "breath/idiom/declare_non_copyable.hpp"
#include "breath/stream/stream_buffer_wrapper.hpp"
#include <istream>
#include <ostream>
#include <streambuf>

namespace breath_ns {

//      null_stream_buffer:
//      -------------------
//
//!     The stream buffer used by \c null_stream.
// ---------------------------------------------------------------------------
class null_stream_buffer
    :   public std::streambuf
{
public:
                        null_stream_buffer() ;

protected:
    //!     \return
    //!         A value which doesn't compare equal to \c Traits::eof()
    //!         (this signals that the output succeeded).
    // -----------------------------------------------------------------------
    virtual int_type    overflow( int_type c ) override ;

    //!     \return
    //!         \c Traits::eof() (this signals that the input reached
    //!         end of file).
    // -----------------------------------------------------------------------
    virtual int_type    underflow() override ;

private:
    void                set_put_area_pointers() ;

    //      Having a buffer avoids some virtual function calls.
    // -----------------------------------------------------------------------
    char_type           m_dummy_buffer[ 64 ] ;
} ;

//      null_stream:
//      ------------
//
//!     A stream that discards any output and provides no input. On
//!     output, the stream never signals failbit. On input it always
//!     signals EOF. The behavior is similar to a file stream opened on
//!     /dev/null under Unix, but this is portable and doesn't make
//!     system calls.
// ---------------------------------------------------------------------------
class null_stream
    :   private stream_buffer_wrapper< null_stream_buffer >,
        public  std::istream,
        public  std::ostream
{
private:
    typedef null_stream_buffer
                        buffer_type ;
    typedef stream_buffer_wrapper< buffer_type >
                        buffer_wrapper_type ;

public:
    BREATH_DECLARE_NON_COPYABLE( null_stream )

                        null_stream() ;
    virtual             ~null_stream() noexcept override = default ;

    null_stream_buffer *
                        rdbuf() const ;
} ;

}

#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
