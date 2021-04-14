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

#ifndef BREEZE_GUARD_CnvhAthmCrzPoNDMrZPUfBrAGrgy3Xe0
#define BREEZE_GUARD_CnvhAthmCrzPoNDMrZPUfBrAGrgy3Xe0

#include "breeze/top_level_namespace.hpp"
#include "breeze/stream/stream_buffer_wrapper.hpp"
#include <istream>
#include <ostream>
#include <streambuf>

namespace breeze_ns {

//      null_stream_buffer:
//      -------------------
//
//!\brief
//!     The stream buffer used by `null_stream`.
// ---------------------------------------------------------------------------
class null_stream_buffer
    :   public std::streambuf
{
public:
                        null_stream_buffer() ;

protected:
    //!     \return
    //!         A value which doesn't compare equal to `Traits::eof()`
    //!         (this signals that the output succeeded).
    // -----------------------------------------------------------------------
    virtual int_type    overflow( int_type c ) override ;

    //!     \return
    //!         `Traits::eof()` (this signals that the input reached end
    //!         of file).
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
//!\brief
//!     A stream that discards any output and provides no input.
//!
//!     On output, the stream never signals failbit. On input, it always
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
    //!     Deleted copy constructor.
    // -----------------------------------------------------------------------
                        null_stream( null_stream const & ) = delete ;

    //!     Deleted copy assignment operator.
    // -----------------------------------------------------------------------
    null_stream &       operator =(  null_stream const & ) = delete ;

                        null_stream() ;
    virtual             ~null_stream() noexcept override = default ;

    null_stream_buffer *
                        rdbuf() const ;
} ;

}

#endif
