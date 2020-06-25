// ===========================================================================
//                        Copyright 2020 Gennaro Prota
//
//                  Licensed under the 3-Clause BSD License.
//             (See accompanying file 3_CLAUSE_BSD_LICENSE.txt or
//              <https://opensource.org/licenses/BSD-3-Clause>.)
// ___________________________________________________________________________
//
//!     \file
//!     \brief Wrapper for a stream buffer.
// ---------------------------------------------------------------------------

#ifndef BREATH_GUARD_HAiCpytMRiUMKQy3v1ioI7B2LEWtzcvv
#define BREATH_GUARD_HAiCpytMRiUMKQy3v1ioI7B2LEWtzcvv

namespace breath {

//      stream_buffer_wrapper:
//      ======================
//
//!     This template is meant to be used to wrap a \c basic_streambuf
//!     when defining a new stream type. In this case, we'd want to have
//!     a stream buffer data member in the derived class, but that would
//!     mean passing its address to the stream base class(es) \e before
//!     its construction (because base subobjects are constructed before
//!     data members).
//!
//!     That's undefined behavior.
//!
//!     Using derivation solves this problem, as long as we can
//!     guarantee that the stream buffer is constructed before the
//!     streams. But it introduces another one: we'd need to pass the \c
//!     this pointer, in the constructor initialization list, to the
//!     base stream constructor(s). Which is probably undefined
//!     behavior, as well.
//!
//!     A solution is to use this wrapper, which allows getting the
//!     contained buffer address without using \c this.
//!
//!     Note that this might become a generic wrapper, but we mean to
//!     only use it for stream buffers, hence its specific name.
//!
//!     An alternative technique to define a stream type would be to \e
//!     default-construct the stream base(s) and have a normal stream
//!     buffer data member; then calling \c std::ios_base::init() with
//!     the address of the buffer from the body of the derived
//!     constructor.
//!
//!     This may lead to multiple calls to \c init(). Which is probably
//!     meant to work, but the standard doesn't make this crystal clear.
//!     So we avoid it, and use this wrapper, instead. (If the standard
//!     was clearer in this regard, I'd prefer this solution.)
// ---------------------------------------------------------------------------
template< typename StreamBufferType >
class stream_buffer_wrapper
{
public:
    StreamBufferType *  stream_buffer() ;

private:
    StreamBufferType    m_buffer ;
} ;

}

#include "brt/stream_buffer_wrapper.tpp"
#endif

// Local Variables:
// mode: c++
// indent-tabs-mode: nil
// c-basic-offset: 4
// End:
// vim: set ft=cpp et sts=4 sw=4:
